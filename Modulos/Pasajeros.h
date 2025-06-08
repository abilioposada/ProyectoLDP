#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../Clases/Pasajero.h"

using namespace std;

/**
 * Función que carga las informacion de archivo externo
 */
vector<Pasajero> cargarPasajeros()
{
	// Inicialización
	ifstream archivo( "Archivos/Pasajeros.txt" );
	vector<Pasajero> pasajeros = {};
	Pasajero pasajero;
	string linea;

	// Si se abrió de manera correcta
	if ( archivo.is_open() )
	{
		// Mientras no llegue al final del archivo
		while ( !archivo.eof() )
		{
			pasajero = Pasajero();

			getline( archivo, linea, ';' );

			// Si la línea no está vacía
			if ( !linea.empty() )
			{
				pasajero.setDoucumentoIdentidad( linea );

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

		// Cerrar archivo
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
 * Función que guarda información en archivo externo
 */
bool guardarPasajeros( vector<Pasajero> pasajeros )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Pasajeros.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Pasajero pasajero : pasajeros )
		{
			archivo << pasajero.toString( ";", false ) << endl;
		}
		
		// Limpia y cierra archivo de escritura
		archivo.close();
		archivo.clear();

		return true;
	}

	cout << "Error en archivo." << endl;
	return false;
}

/**
 * Muestra las información como cadena de caracteres y devuelve listado
 */
vector<Pasajero> listarPasajeros()
{
	// Inicialización
	vector<Pasajero> pasajeros = cargarPasajeros();

	cout << "LISTANDO PASAJEROS" << endl;

	if ( !pasajeros.empty() )
	{
		for ( Pasajero pasajero : pasajeros )
		{
			cout << pasajero.toString() << endl;
		}
	}

	else
	{
		cout << "No hay datos";
	}

	return pasajeros;
}

/**
 * Busca, muestra y retorna
 */
Pasajero buscarPasajero()
{
	cout << "BUSCAR PASAJERO" << endl;

	// Inicialización
	string texto = "";
	bool encontrado = false;
	vector<Pasajero> pasajeros = cargarPasajeros();

	do {
		cout << "Pasajero a buscar: ";
		getline( cin, texto );
		cout << ( texto == "" ? "Favor ingrese dato\n" : "" );
	}
	while( texto == "" );

	// Busca en listado el texto
	for ( Pasajero pasajero : pasajeros )
	{
		if (
			pasajero.getDoucmentoIdentidad() == texto ||
			pasajero.getNacionalidad() == texto ||
			pasajero.getAsiento() == texto ||
			pasajero.getNombre() == texto
		) {
			cout << "El primer resultado que se encontro fue:" << endl;
			cout << pasajero.toString() << endl;
			return pasajero;
		}
	}

	cout << "No encontrado" << endl;
	return Pasajero();
}

/**
 * Solicita datos, agrega a lista y guarda cambios
 */
void solicitarPasajero( int indice = -1, vector<Pasajero> pasajeros = cargarPasajeros() )
{
	// Inicialización
	string linea;
	Pasajero pasajero = Pasajero();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " PASAJERO" << endl;

	// Mantiene identificador
	if ( indice != -1 )
	{
		pasajero.setDoucumentoIdentidad( pasajeros[ indice ].getDoucmentoIdentidad() );
	}

	else
	{
		// Verifica datos únicos
		bool repetido = true;

		while ( repetido )
		{
			repetido = false;

			do {
				cout << "Documento Identidad: ";
				getline( cin, linea );
				cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
			}
			while( linea == "" );

			for ( Pasajero pasajero : pasajeros )
			{
				if ( pasajero.getDoucmentoIdentidad() == linea )
				{
					repetido = true;
					cout << "Dato duplicado, vuelva a intentar" << endl;
					break;
				}
			}
		}

		pasajero.setDoucumentoIdentidad( linea );
	}

	// Nombre
	do {
		cout << "Nombre completo: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );

	pasajero.setNombre( linea );

	// Nacionalidad
	do {
		cout << "Nacionalidad: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );

	pasajero.setNacionalidad( linea );

	// Asiento
	do {
		cout << "Numero de asiento: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );
	
	pasajero.setAsiento( linea );

	switch( indice )
	{
		// Agrega al final de la lista
		case -1: pasajeros.push_back( pasajero ); break;

		// Reemplaza
		default: pasajeros[ indice ] = pasajero; break;
	}

	cout << "Acción realizada de manera " << ( guardarPasajeros( pasajeros ) ? "exitosa" : "erronea" ) << endl;
}

/**
 * Validacion de una acción
 */
void realizarAccionPasajero( string accion = "ELIMINAR" )
{
	cout << accion << " PASAJERO" << endl;

	// Inicialización
	vector<Pasajero> pasajeros = listarPasajeros();
	
	if ( !pasajeros.empty() )
	{
		string documento = "";
		bool encontrado = false;

		// Solicita información
		do {
			cout << "Digite el documento de identidad del pasajero: ";
			getline( cin, documento );
			cout << ( documento == "" ? "Favor ingrese dato\n" : "" );
		}
		while( documento == "" );

		// Busca en listado el identificador
		for ( int i = 0; i < pasajeros.size(); i++ )
		{
			if ( encontrado = pasajeros[ i ].getDoucmentoIdentidad() == documento )
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
 * Submenú
 */
void irModuloPasajeros()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO PASAJEROS" << endl;
		cout << "1) Listar" << endl;
		cout << "2) Buscar" << endl;
		cout << "3) Agregar" << endl;
		cout << "4) Editar" << endl;
		cout << "5) Eliminar" << endl;
		cout << "0) Regresar" << endl << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore();

		switch( opcion )
		{
			case 0: break;
			
			case 1:
				listarPasajeros();
				getchar();
				break;
				
			case 2:
				buscarPasajero();
				getchar();
				break;
			
			case 3:
				solicitarPasajero();
				getchar();
				break;
				
			case 4:
				realizarAccionPasajero( "EDITAR" );
				getchar();
				break;
			
			case 5:
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
