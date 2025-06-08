#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../Clases/Vuelo.h"

using namespace std;

/**
 * Función que carga información de archivo externo
 */
vector<Vuelo> cargarVuelos()
{
	// Inicialización
	ifstream archivo( "Archivos/Vuelos.txt" );
	vector<Vuelo> vuelos = {};
	string linea;
	Vuelo vuelo;

	// Si se abrió de manera correcta
	if ( archivo.is_open() )
	{
		// Mientras no llegue al final del archivo
		while ( !archivo.eof() )
		{
			vuelo = Vuelo();

			getline( archivo, linea, ';' );

			// Si la línea no está vacía
			if ( !linea.empty() )
			{
				vuelo.setCodigo( linea );

				getline( archivo, linea, ';' );
				vuelo.setFechaHoraSalida( linea );

				getline( archivo, linea, ';' );
				vuelo.setFechaHoraLlegada( linea );

				getline( archivo, linea, ';' );
				vuelo.setCapacidad( stoi( linea ) );

				getline( archivo, linea, '\n' );
				vuelo.setTipoAvion( linea );

				vuelos.push_back( vuelo );
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

	return vuelos;
}

/**
 * Función que guarda información en archivo externo
 */
bool guardarRutas( vector<Vuelo> vuelos )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Vuelos.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Vuelo vuelo : vuelos )
		{
			archivo << vuelo.toString( ";" ) << endl;
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
vector<Vuelo> listarVuelos()
{
	// Inicialización
	vector<Vuelo> vuelos = cargarVuelos();

	cout << "LISTANDO VUELOS" << endl;

	if ( !vuelos.empty() )
	{
		for ( Vuelo vuelo : vuelos )
		{
			cout << vuelo.toString() << endl;
		}
	}

	else
	{
		cout << "No hay datos";
	}

	return vuelos;
}

/**
 * Solicita datos, agrega a lista y guarda cambios
 */
void solicitarVuelo( int indice = -1, vector<Vuelo> vuelos = cargarVuelos() )
{
	// Inicialización
	string linea;
	bool repetido = true;
	Vuelo vuelo = Vuelo();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " RUTA" << endl;

	// Mantiene identificador
	if ( indice != -1 )
	{
		vuelo.setCodigo( vuelos[ indice ].getCodigo() );
	}

	else
	{
		// Verifica datos únicos
		while ( repetido )
		{
			repetido = false;

			do {
				cout << "Codigo de vuelo: ";
				getline( cin, linea );
				cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
			}
			while( linea == "" );

			for ( Vuelo vuelo : vuelos )
			{
				if ( vuelo.getCodigo() == linea )
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}

		vuelo.setCodigo( linea );
	}

	// Origen
	do {
		cout << "Fecha y hora de salida: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );

	vuelo.setFechaHoraSalida( linea );

	// Destino
	do {
		cout << "Fecha y hora de llegada: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );
	
	vuelo.setFechaHoraLlegada( linea );

	// Duracion
	do {
		cout << "Capacidad pasajeros: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );
	
	vuelo.setCapacidad( stoi( linea ) );

	// Tarifa
	do {
		cout << "Tipo de avion: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );

	vuelo.setTipoAvion( linea );

	switch( indice )
	{
		// Agrega al final de la lista
		case -1: vuelos.push_back( vuelo ); break;

		// Reemplaza
		default: vuelos[ indice ] = vuelo; break;
	}

	cout << "Acción realizada de manera " << ( guardarRutas( vuelos ) ? "exitosa" : "errónea" ) << endl;
}

/**
 * Validacion de una acción
 */
void realizarAccionVuelo( string accion = "ELIMINAR" )
{
	cout << accion << " RUTA" << endl;

	// Inicialización
	vector<Vuelo> vuelos = listarVuelos();
	
	if ( !vuelos.empty() )
	{
		string codigo = "";
		bool encontrado = false;

		// Solicita información
		do {
			cout << "Digite el codigo de la vuelo: ";
			getline( cin, codigo );
			cout << ( codigo == "" ? "Favor ingrese dato\n" : "" );
		}
		while( codigo == "" );

		// Busca en listado el identificador
		for ( int i = 0; i < vuelos.size(); i++ )
		{
			if ( encontrado = vuelos[ i ].getCodigo() == codigo )
			{
				if ( accion == "ELIMINAR" )
				{
					vuelos.erase( vuelos.begin() + i );
					cout << "Eliminación " << ( guardarRutas( vuelos ) ? "exitosa" : "errónea" ) << endl;
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
 * Submenú
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
		cout << "0) Regresar" << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore();

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
