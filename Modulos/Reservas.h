#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

#include "../Clases/Reserva.h"

using namespace std;

/**
 * Función que carga información de archivo externo
 */
vector<Reserva> cargarReservas()
{
	// Inicialización
	ifstream archivo( "Archivos/Reservas.txt" );
	vector<Reserva> reservas = {};
	string linea;
	Reserva reserva;

	// Si se abrió de manera correcta
	if ( archivo.is_open() )
	{
		// Mientras no llegue al final del archivo
		while ( !archivo.eof() )
		{
			reserva = Reserva();

			getline( archivo, linea, ';' );

			// Si la línea no está vacía
			if ( !linea.empty() )
			{
				reserva.setNumero( linea );

				getline( archivo, linea, ';' );
				reserva.setFechaHora( linea );

				getline( archivo, linea, '\n' );
				reserva.setEstado( static_cast<Reserva::Estado>( stoi( linea ) ) );

				reservas.push_back( reserva );
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

	return reservas;
}

/**
 * Función que guarda información en archivo externo
 */
bool guardarReservas( vector<Reserva> reservas )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Reservas.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Reserva reserva : reservas )
		{
			archivo << reserva.toString( ";", false ) << endl;
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
vector<Reserva> listarReservas()
{
	// Inicialización
	vector<Reserva> reservas = cargarReservas();

	cout << "LISTANDO RESERVAS" << endl;

	if ( !reservas.empty() )
	{
		for ( Reserva reserva : reservas )
		{
			cout << reserva.toString() << endl;
		}
	}

	else
	{
		cout << "No hay datos";
	}

	return reservas;
}

/**
 * Busca, muestra y retorna
 */
Reserva buscarReserva()
{
	cout << "BUSCAR RESERVA" << endl;

	// Inicialización
	string texto = "";
	bool encontrado = false;
	vector<Reserva> reservas = cargarReservas();

	do {
		cout << "Reserva a buscar: ";
		getline( cin, texto );
		cout << ( texto == "" ? "Favor ingrese dato\n" : "" );
	}
	while( texto == "" );

	// Busca en listado el texto
	for ( Reserva reserva : reservas )
	{
		if (
			reserva.getFechaHora() == texto ||
			reserva.getNumero() == texto
		) {
			cout << "El primer resultado que se encontro fue:" << endl;
			cout << reserva.toString() << endl;
			return reserva;
		}
	}

	cout << "No encontrado" << endl;
	return Reserva();
}

/**
 * Solicita datos, agrega a lista y guarda cambios
 */
void solicitarReserva( int indice = -1, vector<Reserva> reservas = cargarReservas() )
{
	// Inicialización
	string linea;
	bool repetido = true;
	Reserva reserva = Reserva();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " RESERVA" << endl;

	// Mantiene identificador
	if ( indice != -1 )
	{
		reserva.setNumero( reservas[ indice ].getNumero() );
	}

	else
	{
		// Verifica datos únicos
		while ( repetido )
		{
			repetido = false;

			do {
				cout << "Numero de reserva: ";
				getline( cin, linea );
				cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
			}
			while( linea == "" );

			for ( Reserva reserva : reservas )
			{
				if ( reserva.getNumero() == linea )
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}

		reserva.setNumero( linea );
	}

	// Fecha hora
	if ( indice != -1 )
	{
		reserva.setFechaHora( reservas[ indice ].getFechaHora() );
	}

	else
	{
		time_t estampaTiempo;
		time( &estampaTiempo );
		reserva.setFechaHora( ctime( &estampaTiempo ) );
	}

	// Estado
	do {
		cout << "Digite estado de reserva:" << endl;
		cout << "1. Pagada" << endl;
		cout << "2. Adeudada" << endl;
		
		getline( cin, linea );
		
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	}
	while( linea == "" );

	if ( stoi( linea ) == 1 )
	{
		reserva.setEstado( Reserva::Estado::PAGADO );
	}

	switch( indice )
	{
		// Agrega al final de la lista
		case -1: reservas.push_back( reserva ); break;

		// Reemplaza
		default: reservas[ indice ] = reserva; break;
	}

	cout << "Acción realizada de manera " << ( guardarReservas( reservas ) ? "exitosa" : "errónea" ) << endl;
}

/**
 * Validacion de una acción
 */
void realizarAccionReserva( string accion = "ELIMINAR" )
{
	cout << accion << " RESERVA" << endl;

	// Inicialización
	vector<Reserva> reservas = listarReservas();
	
	if ( !reservas.empty() )
	{
		string codigo = "";
		bool encontrado = false;

		// Solicita información
		do {
			cout << "Digite el codigo de la reserva: ";
			getline( cin, codigo );
			cout << ( codigo == "" ? "Favor ingrese dato\n" : "" );
		}
		while( codigo == "" );

		// Busca en listado el identificador
		for ( int i = 0; i < reservas.size(); i++ )
		{
			if ( encontrado = reservas[ i ].getNumero() == codigo )
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
 * Submenú
 */
void irModuloReservas()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO RESERVAS" << endl;
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
				listarReservas();
				getchar();
				break;

			case 2:
				buscarReserva();
				getchar();
				break;
				
			case 3:
				solicitarReserva();
				getchar();
				break;
				
			case 4:
				realizarAccionReserva( "EDITAR" );
				getchar();
				break;
			
			case 5:
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
