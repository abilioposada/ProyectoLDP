#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> 

#include "../Clases/Ruta.h"

using namespace std;


vector<Ruta> cargarRutas()
{
	ifstream archivo( "Archivos/Rutas.txt" );
	vector<Ruta> rutas = {};
	string linea;
	Ruta ruta;

	if ( archivo.is_open() )
	{
		while ( !archivo.eof() )
		{
			ruta = Ruta();
			getline( archivo, linea, ';' );
			if ( !linea.empty() )
			{
				ruta.setCodigo( linea );
				getline( archivo, linea, ';' );
				ruta.setOrigen( linea );
				getline( archivo, linea, ';' );
				ruta.setDestino( linea );
				getline( archivo, linea, ';' );
				ruta.setDuracion( stoi( linea ) );
				getline( archivo, linea, '\n' );
				ruta.setTarifa( stof( linea ) );
				rutas.push_back( ruta );
			}
		}
		archivo.close();
		archivo.clear();
	}
	else
	{
		cout << "Error al abrir el archivo no se cargaron datos." << endl;
	}
	return rutas;
}


bool guardarRutas( vector<Ruta> rutas )
{
	ofstream archivo( "Archivos/Rutas.txt" );
	if ( archivo.is_open() )
	{
		for ( const Ruta& ruta : rutas ) 
		{
			archivo << ruta.toString() << endl; 
		}
		archivo.close();
		archivo.clear();
		return true;
	}
	cout << "Error en archivo." << endl;
	return false;
}


vector<Ruta> listarRutas()
{
	vector<Ruta> rutas = cargarRutas();

	cout << "LISTANDO RUTAS" << endl;

	if ( !rutas.empty() )
	{
		cout << left << setw(10) << "CODIGO"
		     << left << setw(15) << "ORIGEN"
		     << left << setw(15) << "DESTINO"
		     << right << setw(10) << "DURACION" 
		     << right << setw(10) << "TARIFA" << endl;
		cout << string(60, '-') << endl; 

		for ( const Ruta& ruta : rutas ) 
		{
			cout << ruta.toString( " ", true ) << endl; 
		}
	}
	else
	{
		cout << "No hay datos";
	}
	cout << endl; // Añade un salto de línea al final por si no hay datos
	return rutas;
}


 // Solicita datos, agrega a lista y guarda cambios
 
void solicitarRuta( int indice = -1, vector<Ruta> rutas = cargarRutas() )
{
	string linea;
	bool repetido = true;
	Ruta ruta = Ruta();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " RUTA" << endl;

	if ( indice != -1 )
	{
		ruta.setCodigo( rutas[ indice ].getCodigo() );
	}
	else
	{
		while ( repetido )
		{
			repetido = false;
			cout << "Codigo de ruta: ";
			getline( cin, linea );
			for ( const Ruta& r : rutas ) // Usar const reference
			{
				if ( r.getCodigo() == linea )
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}
		ruta.setCodigo( linea );
	}

	do {
		cout << "Origen: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	ruta.setOrigen( linea );

	do {
		cout << "Destino: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	ruta.setDestino( linea );

	do {
		cout << "Duracion (minutos): ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	ruta.setDuracion( stoi( linea ) );

	do {
		cout << "Tarifa: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	ruta.setTarifa( stof( linea ) );

	switch( indice )
	{
		case -1: rutas.push_back( ruta ); break;
		default: rutas[ indice ] = ruta; break;
	}

	cout << "Accion realizada de manera " << ( guardarRutas( rutas ) ? "exitosa" : "erronea" ) << endl;
}


void realizarAccionRuta( string accion = "ELIMINAR" )
{
	cout << accion << " RUTA" << endl;
	vector<Ruta> rutas = listarRutas();
	
	if ( !rutas.empty() )
	{
		string codigo = "";
		bool encontrado = false;
		do {
			cout << "Digite el codigo de la ruta: ";
			getline( cin, codigo );
			cout << ( codigo == "" ? "Favor ingrese dato\n" : "" );
		}
		while( codigo == "" );

		for ( int i = 0; i < rutas.size(); i++ )
		{
			if ( encontrado = rutas[ i ].getCodigo() == codigo )
			{
				if ( accion == "ELIMINAR" )
				{
					rutas.erase( rutas.begin() + i );
					cout << "Eliminación " << ( guardarRutas( rutas ) ? "exitosa" : "errónea" ) << endl;
				}
				else
				{
					solicitarRuta( i, rutas );
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
void irModuloRutas()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO RUTAS" << endl;
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
				listarRutas();
				getchar();
				break;
				
			case 2:
				solicitarRuta();
				getchar();
				break;
				
			case 3:
				realizarAccionRuta( "EDITAR" );
				getchar();
				break;
			
			case 4:
				realizarAccionRuta( "ELIMINAR" );
				getchar();
				break;
				
			default:
				cout << "No ha seleccionado una opcion valida" << endl;
				getchar();
				break;
		}
	}
}