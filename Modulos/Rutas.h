#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../Clases/Ruta.h"

using namespace std;

/**
 * Función que carga información de archivo externo
 */
vector<Ruta> cargarRutas()
{
	// Inicialización
	ifstream archivo( "Archivos/Rutas.txt" );
	vector<Ruta> rutas = {};
	string linea;
	Ruta ruta;

	// Si se abrió de manera correcta
	if ( archivo.is_open() )
	{
		// Mientras no llegue al final del archivo
		while ( !archivo.eof() )
		{
			ruta = Ruta();

			getline( archivo, linea, ';' );

			// Si la línea no está vacía
			if ( !linea.empty() )
			{
				ruta.setId( stoi( linea ) );

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

		// Cerrar archivo
		archivo.close();
		archivo.clear();
	}

	else
	{
		cout << "Error al abrir el archivo no se cargaron datos." << endl;
	}

	return rutas;
}

/**
 * Función que guarda información en archivo externo
 */
bool guardarRutas( vector<Ruta> rutas )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Rutas.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Ruta ruta : rutas )
		{
			archivo << ruta.toString( ';' ) << endl;
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
vector<Ruta> listarRutas()
{
	// Inicialización
	vector<Ruta> rutas = cargarRutas();

	cout << "LISTANDO RUTAS" << endl;

	if ( !rutas.empty() )
	{
		for ( Ruta ruta : rutas )
		{
			cout << ruta.toString() << endl;
		}
	}

	else
	{
		cout << "No hay datos";
	}

	return rutas;
}

/**
 * Solicita datos, agrega a lista y guarda cambios
 */
void solicitarRuta( int indice = -1, vector<Ruta> rutas = cargarRutas() )
{
	// Inicialización
	string linea;
	Ruta ruta = Ruta();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " RUTA" << endl;

	// Identificador automatizado
	ruta.setId( indice != -1 ? rutas[ indice ].getId() : ( rutas.empty() ? 1 : rutas[ rutas.size() - 1 ].getId() + 1 ) );

	cout << "Origen: ";
	getline( cin, linea );
	ruta.setOrigen( linea );

	cout << "Destino: ";
	getline( cin, linea );
	ruta.setDestino( linea );

	cout << "Duracion en minutos: ";
	getline( cin, linea );
	ruta.setDuracion( stoi( linea ) );

	cout << "Tarifa en USD: ";
	getline( cin, linea );
	ruta.setTarifa( stof( linea ) );

	if ( indice != -1 )
	{
		rutas[ indice ] = ruta;
	}

	else
	{
		rutas.push_back( ruta );
	}

	cout << "Acción realizada de manera " << ( guardarRutas( rutas ) ? "exitosa" : "errónea" ) << endl;
}

/**
 * Validacion de una acción
 */
void realizarAccionRuta( string accion = "ELIMINAR" )
{
	cout << accion << " RUTA" << endl;

	// Inicialización
	vector<Ruta> rutas = listarRutas();
	
	if ( !rutas.empty() )
	{
		int id = 0;

		// Solicita información
		cout << "Digite el id de la ruta: ";
		cin >> id;
		cin.ignore();

		bool encontrado = false;

		// Busca en listado el identificador
		for ( int i = 0; i < rutas.size(); i++ )
		{
			if ( encontrado = rutas[ i ].getId() == id )
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
 * Submenú
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
		cout << "0) Regresar" << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore();

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
