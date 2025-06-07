#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../Clases/Ruta.h"

using namespace std;

void listarRutas();
void agregarRuta();

void irModuloRutas()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		cout << "MODULO RUTAS" << endl;
		cout << "1) Listar" << endl;
		cout << "2) Agregar" << endl;
		cout << "3) Eliminar" << endl;
		cout << "0) Regresar" << endl;

		cout << "Elija opcion: ";
		cin >> opcion;

		switch( opcion )
		{
			case 0: break;
			
			case 1:
				listarRutas();
				break;
				
			case 2:
				agregarRuta();
				break;
				
			case 3:
				break;
				
			default:
				cout << "No ha seleccionado opcion valida" << endl << endl;
				break;
		}
	}
}

vector<Ruta> cargarRutas()
{
	ifstream archivo( "Archivos/Rutas.txt" );
	string linea;
	vector<Ruta> rutas = {};
	Ruta ruta;

	if ( archivo.is_open() )
	{
		while ( !archivo.eof() )
		{
			ruta = Ruta();

			getline( archivo, linea, ';' );
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

		archivo.close();
	}

	else
	{
		cout << "Error al abrir el archivo.\n";
	}

	return rutas;
}

void listarRutas()
{
	vector<Ruta> rutas = cargarRutas();

	cout << "LISTANDO RUTAS" << endl;

	for ( Ruta ruta : rutas )
	{
		cout << ruta.toString() << endl;
	}
}

bool guardarRutas( vector<Ruta> nuevasRutas )
{
	// Abre archivo para escritura y sobreescribe
	ofstream archivo( "Archivos/Rutas.txt" );
	
	if ( archivo.is_open() )
	{
		for ( Ruta ruta : nuevasRutas )
		{
			archivo << ruta.toString( ';' ) << endl;
		}
		
		// Limpia y cierra archivo de escritura
		archivo.close();
		archivo.clear();

		return true;
	}

	cout << "Error en archivo" << endl;
	return false;
}

void agregarRuta()
{
	Ruta ruta = Ruta( 5, "El Salvador", "Guatemala", 30, 105 );
	vector<Ruta> rutas = cargarRutas();

	cout << "AGREGAR RUTA" << endl;

	rutas.push_back( ruta );

	if ( guardarRutas( rutas ) )
	{
		cout << "Ruta agregada correctamente" << endl;
	}

	else
	{
		cout << "No se pudo agregar la ruta" << endl;
	}
}
