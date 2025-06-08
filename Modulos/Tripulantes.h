#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../Clases/Tripulante.h"

using namespace std;

/**
 * Función que carga las informacion de archivo externo
 */
vector<Tripulante> cargarTripulantes()
{
	// Inicialización
	ifstream archivo( "Archivos/Tripulantes.txt" );
	vector<Tripulante> tripulantes = {};
	Tripulante tripulante;
	string linea;

	// Si se abrió de manera correcta
	if ( archivo.is_open() )
	{
		// Mientras no llegue al final del archivo
		while ( !archivo.eof() )
		{
			tripulante = Tripulante();

			getline( archivo, linea, ';' );

			// Si la línea no está vacía
			if ( !linea.empty() )
			{
				tripulante.setCodigo( linea );
				
				getline( archivo, linea, ';' );
				tripulante.setDoucumentoIdentidad( linea );
				
				getline( archivo, linea, ';' );
				tripulante.setNombre( linea );
				
				getline( archivo, linea, ';' );
				tripulante.setNacionalidad( linea );

				getline( archivo, linea, '\n' );
				tripulante.setRol( static_cast<Tripulante::Rol>( stoi( linea ) ) );

				tripulantes.push_back( tripulante );
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

	return tripulantes;
}

/**
 * Función que guarda información en archivo externo
 */
bool guardarTripulantes( vector<Tripulante> tripulantes )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Tripulantes.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Tripulante tripulante : tripulantes )
		{
			archivo << tripulante.toString( ";", false ) << endl;
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
vector<Tripulante> listarTripulantes()
{
	// Inicialización
	vector<Tripulante> tripulantes = cargarTripulantes();

	cout << "LISTANDO TRIPULANTES" << endl;

	if ( !tripulantes.empty() )
	{
		for ( Tripulante tripulante : tripulantes )
		{
			cout << tripulante.toString() << endl;
		}
	}

	else
	{
		cout << "No hay datos";
	}

	return tripulantes;
}

/**
 * Solicita datos, agrega a lista y guarda cambios
 */
void solicitarTripulante( int indice = -1, vector<Tripulante> tripulantes = cargarTripulantes() )
{
	// Inicialización
	string linea;
	bool repetido = true;
	Tripulante tripulante = Tripulante();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " TRIPULANTE" << endl;

	// Mantiene identificador
	if ( indice != -1 )
	{
		tripulante.setCodigo( tripulantes[ indice ].getCodigo() );
	}

	else
	{
		// Verifica datos únicos
		while ( repetido )
		{
			repetido = false;

			cout << "Codigo de tripulante: ";
			getline( cin, linea );

			for ( Tripulante tripulante : tripulantes )
			{
				if ( tripulante.getCodigo() == linea )
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}

		tripulante.setCodigo( linea );
	}

	// Verifica datos únicos
	repetido = true;

	while ( repetido )
	{
		repetido = false;

		cout << "Documento Identidad: ";
		getline( cin, linea );

		for ( Tripulante tripulante : tripulantes )
		{
			if ( tripulante.getDoucmentoIdentidad() == linea )
			{
				cout << "Dato duplicado, vuelva a intentar" << endl;
				repetido = true;
				break;
			}
		}
	}

	tripulante.setDoucumentoIdentidad( linea );

	cout << "Nombre completo: ";
	getline( cin, linea );
	tripulante.setNombre( linea );

	cout << "Nacionalidad: ";
	getline( cin, linea );
	tripulante.setNacionalidad( linea );

	cout << "Digite numero de rol:" << endl;
	cout << "1. Piloto" << endl;
	cout << "2. Copiloto" << endl;
	cout << "3. Auxiliar" << endl;
	cin >> linea;

	switch ( stoi( linea ) )
	{
		case 1: tripulante.setRol( Tripulante::Rol::PILOTO ); break;

		case 2: tripulante.setRol( Tripulante::Rol::COPILOTO ); break;

		default: tripulante.setRol( Tripulante::Rol::AUXILIAR ); break;
	};

	if ( indice != -1 )
	{
		tripulantes[ indice ] = tripulante;
	}

	else
	{
		tripulantes.push_back( tripulante );
	}

	cout << "Accion realizada de manera " << ( guardarTripulantes( tripulantes ) ? "exitosa" : "erronea" ) << endl;
}

/**
 * Validacion de una acción
 */
void realizarAccionTripulante( string accion = "ELIMINAR" )
{
	cout << accion << " TRIPULANTE" << endl;

	// Inicialización
	vector<Tripulante> tripulantes = listarTripulantes();
	
	if ( !tripulantes.empty() )
	{
		string codigo = "";

		// Solicita información
		cout << "Digite el codigo del tripulante: ";
		getline( cin, codigo );

		bool encontrado = false;

		// Busca en listado el identificador
		for ( int i = 0; i < tripulantes.size(); i++ )
		{
			if ( encontrado = tripulantes[ i ].getCodigo() == codigo )
			{
				if ( accion == "ELIMINAR" )
				{
					tripulantes.erase( tripulantes.begin() + i );
					cout << "Eliminacion " << ( guardarTripulantes( tripulantes ) ? "exitosa" : "erronea" ) << endl;
				}

				else
				{
					solicitarTripulante( i, tripulantes );
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
void irModuloTripulantes()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MODULO TRIPULANTES" << endl;
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
				listarTripulantes();
				getchar();
				break;
				
			case 2:
				solicitarTripulante();
				getchar();
				break;
				
			case 3:
				realizarAccionTripulante( "EDITAR" );
				getchar();
				break;
			
			case 4:
				realizarAccionTripulante( "ELIMINAR" );
				getchar();
				break;
				
			default:
				cout << "No ha seleccionado una opcion valida" << endl;
				getchar();
				break;
		}
	}
}
