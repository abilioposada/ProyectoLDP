#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> 

#include "../Clases/Vuelo.h"
#include "Rutas.h"
#include "Tripulantes.h"

using namespace std;


vector<Vuelo> cargarVuelos()
{
    ifstream archivo( "Archivos/Vuelos.txt" );
    vector<Vuelo> vuelos = {};
    string linea;
    Vuelo vuelo;

    if ( archivo.is_open() )
    {
        while ( !archivo.eof() )
        {
            vuelo = Vuelo();
            getline( archivo, linea, ';' );
            if ( !linea.empty() )
            {
                vuelo.setCodigo( linea );
                getline( archivo, linea, ';' );
                vuelo.setFechaHoraSalida( linea );
                getline( archivo, linea, ';' );
                vuelo.setFechaHoraLlegada( linea );
                getline( archivo, linea, ';' );
                vuelo.setCapacidad( stoi( linea ) );
                getline( archivo, linea, ';' );
                vuelo.setTipoAvion( linea );

                // Cargar Ruta por codigo
                getline( archivo, linea, ';' );
                string codigoRuta = linea;
                vector<Ruta> rutasExistentes = cargarRutas(); // Carga todas las rutas
                for ( const Ruta& r : rutasExistentes ) {
                    if ( r.getCodigo() == codigoRuta ) {
                        vuelo.setRuta( r );
                        break;
                    }
                }

                getline( archivo, linea, '\n' );
                string tripulantesCodigosStr = linea;
                vector<Tripulante> tripulantesVuelo;
                if (!tripulantesCodigosStr.empty()) {
                    stringstream ss(tripulantesCodigosStr);
                    string tripulanteCodigo;
                    vector<Tripulante> tripulantesExistentes = cargarTripulantes(); // Carga todos los tripulantes
                    while (getline(ss, tripulanteCodigo, ',')) {
                        for ( const Tripulante& t : tripulantesExistentes ) {
                            if ( t.getCodigo() == tripulanteCodigo ) {
                                tripulantesVuelo.push_back( t );
                                break;
                            }
                        }
                    }
                }
                vuelo.setTripulantes(tripulantesVuelo);

                vuelos.push_back( vuelo );
            }
        }
        archivo.close();
        archivo.clear();
    }
    else
    {
        cout << "Error al abrir el archivo no se cargaron datos." << endl;
    }
    return vuelos;
}


bool guardarVuelos( vector<Vuelo> vuelos )
{
	ofstream archivo( "Archivos/Vuelos.txt" );
	if ( archivo.is_open() )
	{
		for ( const Vuelo& vuelo : vuelos )
		{
			archivo << vuelo.toString( ";" ) << endl; 
		}
		archivo.close();
		archivo.clear();
		return true;
	}
	cout << "Error en archivo." << endl;
	return false;
}


vector<Vuelo> listarVuelos()
{
	vector<Vuelo> vuelos = cargarVuelos();

	cout << "LISTANDO VUELOS" << endl;

	if ( !vuelos.empty() )
	{
		cout << left << setw(10) << "CODIGO"
		     << left << setw(20) << "SALIDA"
		     << left << setw(20) << "LLEGADA"
		     << right << setw(10) << "CAPACIDAD"
		     << left << setw(15) << "TIPO AVION"
		     << left << setw(10) << "RUTA" << endl;
		cout << string(85, '-') << endl; 

		for ( const Vuelo& vuelo : vuelos )
		{
			cout << vuelo.toString( " ", true ) << endl; 
		}
	}
	else
	{
		cout << "No hay datos";
	}
	cout << endl;
	return vuelos;
}


void solicitarVuelo( int indice = -1, vector<Vuelo> vuelos = cargarVuelos() )
{
    string linea;
    bool repetido = true;
    Vuelo vuelo = Vuelo();

    cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " VUELO" << endl;

    if ( indice != -1 )
    {
        vuelo.setCodigo( vuelos[ indice ].getCodigo() );
    }
    else
    {
        while ( repetido )
        {
            repetido = false;
            cout << "Codigo de vuelo: ";
            getline( cin, linea );
            for ( const Vuelo& v : vuelos )
            {
                if ( v.getCodigo() == linea )
                {
                    cout << "Dato duplicado, vuelva a intentar" << endl;
                    repetido = true;
                    break;
                }
            }
        }
        vuelo.setCodigo( linea );
    }

    do {
        cout << "Fecha y Hora de Salida (AAAA-MM-DD HH:MM): ";
        getline( cin, linea );
        cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
    } while( linea == "" );
    vuelo.setFechaHoraSalida( linea );

    do {
        cout << "Fecha y Hora de Llegada (AAAA-MM-DD HH:MM): ";
        getline( cin, linea );
        cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
    } while( linea == "" );
    vuelo.setFechaHoraLlegada( linea );

    do {
        cout << "Capacidad: ";
        getline( cin, linea );
        cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
    } while( linea == "" );
    vuelo.setCapacidad( stoi( linea ) );

    do {
        cout << "Tipo de Avión: ";
        getline( cin, linea );
        cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
    } while( linea == "" );
    vuelo.setTipoAvion( linea );

    // Selección de Ruta
    vector<Ruta> rutasDisponibles = listarRutas(); // Muestra las rutas disponibles
    if (!rutasDisponibles.empty()) {
        string codigoRuta;
        bool rutaEncontrada = false;
        do {
            cout << "Ingrese el codigo de la Ruta para el vuelo: ";
            getline( cin, codigoRuta );
            for ( const Ruta& r : rutasDisponibles ) {
                if ( r.getCodigo() == codigoRuta ) {
                    vuelo.setRuta( r );
                    rutaEncontrada = true;
                    break;
                }
            }
            if (!rutaEncontrada) {
                cout << "Codigo de ruta no encontrado. Intente de nuevo.\n";
            }
        } while( !rutaEncontrada );
    } else {
        cout << "No hay rutas disponibles. Por favor, agregue rutas primero." << endl;
        getchar();
        return; // Sale de la funcion si no hay rutas
    }

    

    switch( indice )
    {
        case -1: vuelos.push_back( vuelo ); break;
        default: vuelos[ indice ] = vuelo; break;
    }

    cout << "Accion realizada de manera " << ( guardarVuelos( vuelos ) ? "exitosa" : "erronea" ) << endl;
}



void realizarAccionVuelo( string accion = "ELIMINAR" )
{
	cout << accion << " VUELO" << endl;
	vector<Vuelo> vuelos = listarVuelos();
	
	if ( !vuelos.empty() )
	{
		string codigo = "";
		bool encontrado = false;
		do {
			cout << "Digite el codigo del vuelo: ";
			getline( cin, codigo );
			cout << ( codigo == "" ? "Favor ingrese dato\n" : "" );
		}
		while( codigo == "" );

		for ( int i = 0; i < vuelos.size(); i++ )
		{
			if ( encontrado = vuelos[ i ].getCodigo() == codigo )
			{
				if ( accion == "ELIMINAR" )
				{
					vuelos.erase( vuelos.begin() + i );
					cout << "Eliminación " << ( guardarVuelos( vuelos ) ? "exitosa" : "errónea" ) << endl; 
				}
				else
				{
					solicitarVuelo( i, vuelos );
				}
				break;
			}
		}
		cout << ( !encontrado ? "Identificador no encontrado\n" : "" );
	}
}

/**
 * Submenu
 */
void irModuloVuelos()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO VUELOS" << endl;
		cout << "1) Listar" << endl;
		cout << "2) Agregar" << endl;
		cout << "3) Editar" << endl;
		cout << "4) Eliminar" << endl;
		cout << "0) Regresar" << endl << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore(); // Limpiar el buffer de entrada

		switch( opcion )
		{
			case 0: break;
			
			case 1:
				listarVuelos();
				getchar();
				break;
				
			case 2:
				solicitarVuelo();
				getchar();
				break;
				
			case 3:
				realizarAccionVuelo( "EDITAR" );
				getchar();
				break;
			
			case 4:
				realizarAccionVuelo( "ELIMINAR" );
				getchar();
				break;
				
			default:
				cout << "No ha seleccionado una opcion valida" << endl;
				getchar();
				break;
		}
	}
}