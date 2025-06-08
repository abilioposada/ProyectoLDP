#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>     
#include <iomanip>   

#include "../Clases/Reserva.h"
#include "Vuelos.h"    
#include "Pasajeros.h" 

using namespace std;


vector<Reserva> cargarReservas()
{
	ifstream archivo( "Archivos/Reservas.txt" );
	vector<Reserva> reservas = {};
	string linea;
	Reserva reserva;

	if ( archivo.is_open() )
	{
		while ( !archivo.eof() )
		{
			reserva = Reserva();
			getline( archivo, linea, ';' );
			if ( !linea.empty() )
			{
				reserva.setNumero( linea );
				getline( archivo, linea, ';' );
				reserva.setFechaHora( linea );
				getline( archivo, linea, ';' ); // Leer estado
				reserva.setEstado( static_cast<Reserva::Estado>( stoi( linea ) ) );
				
				getline( archivo, linea, ';' ); 
				string codigoVuelo = linea;
				vector<Vuelo> vuelosExistentes = cargarVuelos();
				for ( const Vuelo& v : vuelosExistentes ) {
					if ( v.getCodigo() == codigoVuelo ) {
						reserva.setVuelo( v );
						break;
					}
				}

				getline( archivo, linea, '\n' ); 
				string documentoPasajero = linea;
				vector<Pasajero> pasajerosExistentes = cargarPasajeros();
				for ( const Pasajero& p : pasajerosExistentes ) {
					if ( p.getDocumentoIdentidad() == documentoPasajero ) {
						reserva.setPasajero( p );
						break;
					}
				}
				
				reservas.push_back( reserva );
			}
		}
		archivo.close();
		archivo.clear();
	}
	else
	{
		cout << "Error al abrir el archivo no se cargaron datos." << endl;
	}
	return reservas;
}


bool guardarReservas( vector<Reserva> reservas )
{
	ofstream archivo( "Archivos/Reservas.txt" );
	if ( archivo.is_open() )
	{
		for ( const Reserva& reserva : reservas )
		{
			archivo << reserva.toString( ";" ) << endl; 
		}
		archivo.close();
		archivo.clear();
		return true;
	}
	cout << "Error en archivo." << endl;
	return false;
}


vector<Reserva> listarReservas()
{
	vector<Reserva> reservas = cargarReservas();

	cout << "LISTANDO RESERVAS" << endl;

	if ( !reservas.empty() )
	{
		cout << left << setw(10) << "NUMERO"
		     << left << setw(20) << "FECHA/HORA"
		     << left << setw(15) << "ESTADO"
		     << left << setw(10) << "VUELO"
		     << left << setw(15) << "PASAJERO (Doc)" << endl;
		cout << string(70, '-') << endl; 

		for ( const Reserva& reserva : reservas )
		{
			cout << reserva.toString( " ", true ) << endl; 
		}
	}
	else
	{
		cout << "No hay datos";
	}
	cout << endl;
	return reservas;
}


void solicitarReserva( int indice = -1, vector<Reserva> reservas = cargarReservas() )
{
    string linea;
    bool repetido = true;
    Reserva reserva = Reserva();

    cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " RESERVA" << endl;

    if ( indice != -1 )
    {
        reserva.setNumero( reservas[ indice ].getNumero() );
    }
    else
    {
        while ( repetido )
        {
            repetido = false;
            cout << "Numero de reserva: ";
            getline( cin, linea );
            for ( const Reserva& r : reservas )
            {
                if ( r.getNumero() == linea )
                {
                    cout << "Dato duplicado, vuelva a intentar" << endl;
                    repetido = true;
                    break;
                }
            }
        }
        reserva.setNumero( linea );
    }

    do {
        cout << "Fecha y Hora de Reserva (AAAA-MM-DD HH:MM): ";
        getline( cin, linea );
        cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
    } while( linea == "" );
    reserva.setFechaHora( linea );

    int estadoOpcion;
    cout << "Estado (1: ADEUDADO, 2: PAGADO): ";
    cin >> estadoOpcion;
    cin.ignore();
    reserva.setEstado( static_cast<Reserva::Estado>( estadoOpcion - 1 ) );

    // Selección de Vuelo
    vector<Vuelo> vuelosDisponibles = listarVuelos(); // Muestra los vuelos disponibles
    if (!vuelosDisponibles.empty()) {
        string codigoVuelo;
        bool vueloEncontrado = false;
        do {
            cout << "Ingrese el codigo del Vuelo para la reserva: ";
            getline( cin, codigoVuelo );
            for ( const Vuelo& v : vuelosDisponibles ) {
                if ( v.getCodigo() == codigoVuelo ) {
                    reserva.setVuelo( v );
                    vueloEncontrado = true;
                    break;
                }
            }
            if (!vueloEncontrado) {
                cout << "Codigo de vuelo no encontrado. Intente de nuevo.\n";
            }
        } while( !vueloEncontrado );
    } else {
        cout << "No hay vuelos disponibles. Por favor, agregue vuelos primero." << endl;
        getchar();
        return;
    }

    // Selección de Pasajero
    vector<Pasajero> pasajerosDisponibles = listarPasajeros(); // Muestra los pasajeros disponibles
    if (!pasajerosDisponibles.empty()) {
        string documentoPasajero;
        bool pasajeroEncontrado = false;
        do {
            cout << "Ingrese el documento de identidad del Pasajero para la reserva: ";
            getline( cin, documentoPasajero );
            for ( const Pasajero& p : pasajerosDisponibles ) {
                if ( p.getDocumentoIdentidad() == documentoPasajero ) {
                    reserva.setPasajero( p );
                    pasajeroEncontrado = true;
                    break;
                }
            }
            if (!pasajeroEncontrado) {
                cout << "Documento de identidad de pasajero no encontrado. Intente de nuevo.\n";
            }
        } while( !pasajeroEncontrado );
    } else {
        cout << "No hay pasajeros disponibles. Por favor, agregue pasajeros primero." << endl;
        getchar();
        return;
    }

    switch( indice )
    {
        case -1: reservas.push_back( reserva ); break;
        default: reservas[ indice ] = reserva; break;
    }

    cout << "Accion realizada de manera " << ( guardarReservas( reservas ) ? "exitosa" : "erronea" ) << endl;
}


void realizarAccionReserva( string accion = "ELIMINAR" )
{
	cout << accion << " RESERVA" << endl;
	vector<Reserva> reservas = listarReservas();
	
	if ( !reservas.empty() )
	{
		string numero = "";
		bool encontrado = false;
		do {
			cout << "Digite el numero de la reserva: ";
			getline( cin, numero );
			cout << ( numero == "" ? "Favor ingrese dato\n" : "" );
		}
		while( numero == "" );

		for ( int i = 0; i < reservas.size(); i++ )
		{
			if ( encontrado = reservas[ i ].getNumero() == numero )
			{
				if ( accion == "ELIMINAR" )
				{
					reservas.erase( reservas.begin() + i );
					cout << "Eliminación " << ( guardarReservas( reservas ) ? "exitosa" : "errónea" ) << endl; 
				}
				else
				{
					solicitarReserva( i, reservas );
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
void irModuloReservas()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO RESERVAS" << endl;
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
				listarReservas();
				getchar();
				break;
				
			case 2:
				solicitarReserva();
				getchar();
				break;
				
			case 3:
				realizarAccionReserva( "EDITAR" );
				getchar();
				break;
			
			case 4:
				realizarAccionReserva( "ELIMINAR" );
				getchar();
				break;
				
			default:
				cout << "No ha seleccionado una opcion valida" << endl;
				getchar();
				break;
		}
	}
}