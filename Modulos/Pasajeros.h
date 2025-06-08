#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "../Clases/Pasajero.h" 

using namespace std;


vector<Pasajero> cargarPasajeros()
{
	ifstream archivo( "Archivos/Pasajeros.txt" );
	vector<Pasajero> pasajeros = {};
	Pasajero pasajero;
	string linea;

	if ( archivo.is_open() )
	{
		while ( !archivo.eof() )
		{
			pasajero = Pasajero();
			getline( archivo, linea, ';' );
			if ( !linea.empty() )
			{
				pasajero.setDocumentoIdentidad( linea );
				getline( archivo, linea, ';' );
				pasajero.setNombre( linea );
				getline( archivo, linea, ';' );
				pasajero.setNacionalidad( linea );
				getline( archivo, linea, ';' );
				pasajero.setAsiento( linea );
				getline( archivo, linea, '\n' );
				pasajero.setEstado( static_cast<Pasajero::Estado>( stoi( linea ) ) );
				pasajeros.push_back( pasajero );
			}
		}
		archivo.close();
		archivo.clear();
	}
	else
	{
		cout << "Error al abrir el archivo no se cargaron datos." << endl;
	}
	return pasajeros;
}

/**
 * Funcion que guarda información en archivo externo
 */
bool guardarPasajeros( vector<Pasajero> pasajeros )
{
	ofstream archivo( "Archivos/Pasajeros.txt" );
	if ( archivo.is_open() )
	{
		for ( const Pasajero& pasajero : pasajeros )
		{
			archivo << pasajero.toString( ";" ) << endl; 
		}
		archivo.close();
		archivo.clear();
		return true;
	}
	cout << "Error en archivo." << endl;
	return false;
}

/**
 * Muestra la informacion como cadena de caracteres y devuelve listado
 */
vector<Pasajero> listarPasajeros()
{
	vector<Pasajero> pasajeros = cargarPasajeros();

	cout << "LISTANDO PASAJEROS" << endl;

	if ( !pasajeros.empty() )
	{
		cout << left << setw(15) << "DOCUMENTO"
		     << left << setw(25) << "NOMBRE"
		     << left << setw(20) << "NACIONALIDAD"
		     << left << setw(10) << "ASIENTO"
		     << left << setw(15) << "ESTADO" << endl;
		cout << string(85, '-') << endl;

		for ( const Pasajero& pasajero : pasajeros )
		{
			cout << pasajero.toString( " ", true ) << endl;
		}
	}
	else
	{
		cout << "No hay datos";
	}
	cout << endl;
	return pasajeros;
}


void solicitarPasajero( int indice = -1, vector<Pasajero> pasajeros = cargarPasajeros() )
{
	string linea;
	bool repetido = true;
	Pasajero pasajero = Pasajero();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " PASAJERO" << endl;

	if ( indice != -1 )
	{
		pasajero.setDocumentoIdentidad( pasajeros[ indice ].getDocumentoIdentidad() ); 
	}
	else
	{
		while ( repetido )
		{
			repetido = false;
			cout << "Documento de identidad: ";
			getline( cin, linea );
			for ( const Pasajero& p : pasajeros )
			{
				if ( p.getDocumentoIdentidad() == linea ) 
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}
		pasajero.setDocumentoIdentidad( linea ); 
	}

	do {
		cout << "Nombre: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	pasajero.setNombre( linea );

	do {
		cout << "Nacionalidad: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	pasajero.setNacionalidad( linea );

	do {
		cout << "Asiento: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	pasajero.setAsiento( linea );

	int estadoOpcion;
	cout << "Estado (1: NOVALIDADO, 2: VALIDADO): ";
	cin >> estadoOpcion;
	cin.ignore();
	pasajero.setEstado( static_cast<Pasajero::Estado>( estadoOpcion - 1 ) ); 

	switch( indice )
	{
		case -1: pasajeros.push_back( pasajero ); break;
		default: pasajeros[ indice ] = pasajero; break;
	}

	cout << "Accion realizada de manera " << ( guardarPasajeros( pasajeros ) ? "exitosa" : "erronea" ) << endl;
}

/**
 * Validacion de una accion
 */
void realizarAccionPasajero( string accion = "ELIMINAR" )
{
	cout << accion << " PASAJERO" << endl;
	vector<Pasajero> pasajeros = listarPasajeros();
	
	if ( !pasajeros.empty() )
	{
		string documento = "";
		bool encontrado = false;
		do {
			cout << "Digite el documento de identidad del pasajero: ";
			getline( cin, documento );
			cout << ( documento == "" ? "Favor ingrese dato\n" : "" );
		}
		while( documento == "" );

		for ( int i = 0; i < pasajeros.size(); i++ )
		{
			if ( encontrado = pasajeros[ i ].getDocumentoIdentidad() == documento ) 
			{
				if ( accion == "ELIMINAR" )
				{
					pasajeros.erase( pasajeros.begin() + i );
					cout << "Eliminación " << ( guardarPasajeros( pasajeros ) ? "exitosa" : "errónea" ) << endl;
				}
				else
				{
					solicitarPasajero( i, pasajeros );
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
void irModuloPasajeros()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO PASAJEROS" << endl;
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
				listarPasajeros();
				getchar();
				break;
				
			case 2:
				solicitarPasajero();
				getchar();
				break;
				
			case 3:
				realizarAccionPasajero( "EDITAR" );
				getchar();
				break;
			
			case 4:
				realizarAccionPasajero( "ELIMINAR" );
				getchar();
				break;
				
			default:
				cout << "No ha seleccionado una opcion valida" << endl;
				getchar();
				break;
		}
	}
}