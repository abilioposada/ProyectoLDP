#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> 

#include "../Clases/Tripulante.h" 

using namespace std;


vector<Tripulante> cargarTripulantes()
{
	ifstream archivo( "Archivos/Tripulantes.txt" );
	vector<Tripulante> tripulantes = {};
	Tripulante tripulante;
	string linea;

	if ( archivo.is_open() )
	{
		while ( !archivo.eof() )
		{
			tripulante = Tripulante();
			getline( archivo, linea, ';' );
			if ( !linea.empty() )
			{
				tripulante.setCodigo( linea );
				getline( archivo, linea, ';' );
				tripulante.setDocumentoIdentidad( linea ); 
				getline( archivo, linea, ';' );
				tripulante.setNombre( linea );
				getline( archivo, linea, ';' );
				tripulante.setNacionalidad( linea );
				getline( archivo, linea, '\n' );
				tripulante.setRol( static_cast<Tripulante::Rol>( stoi( linea ) ) );
				tripulantes.push_back( tripulante );
			}
		}
		archivo.close();
		archivo.clear();
	}
	else
	{
		cout << "Error al abrir el archivo no se cargaron datos." << endl;
	}
	return tripulantes;
}


bool guardarTripulantes( vector<Tripulante> tripulantes )
{
	ofstream archivo( "Archivos/Tripulantes.txt" );
	if ( archivo.is_open() )
	{
		for ( const Tripulante& tripulante : tripulantes )
		{
			archivo << tripulante.toString( ";" ) << endl; 
		}
		archivo.close();
		archivo.clear();
		return true;
	}
	cout << "Error en archivo." << endl;
	return false;
}


vector<Tripulante> listarTripulantes()
{
	vector<Tripulante> tripulantes = cargarTripulantes();

	cout << "LISTANDO TRIPULANTES" << endl;

	if ( !tripulantes.empty() )
	{
		cout << left << setw(15) << "DOCUMENTO"
		     << left << setw(25) << "NOMBRE"
		     << left << setw(20) << "NACIONALIDAD"
		     << left << setw(10) << "CODIGO"
		     << left << setw(15) << "ROL" << endl;
		cout << string(90, '-') << endl; 

		for ( const Tripulante& tripulante : tripulantes )
		{
			cout << tripulante.toString( " ", true ) << endl; 
		}
	}
	else
	{
		cout << "No hay datos";
	}
	cout << endl;
	return tripulantes;
}


void solicitarTripulante( int indice = -1, vector<Tripulante> tripulantes = cargarTripulantes() )
{
	string linea;
	bool repetido = true;
	Tripulante tripulante = Tripulante();

	cout << ( indice != -1 ? "EDITAR" : "AGREGAR" ) << " TRIPULANTE" << endl;

	if ( indice != -1 )
	{
		tripulante.setCodigo( tripulantes[ indice ].getCodigo() );
	}
	else
	{
		while ( repetido )
		{
			repetido = false;
			cout << "Codigo de tripulante: ";
			getline( cin, linea );
			for ( const Tripulante& t : tripulantes )
			{
				if ( t.getCodigo() == linea )
				{
					cout << "Dato duplicado, vuelva a intentar" << endl;
					repetido = true;
					break;
				}
			}
		}
		tripulante.setCodigo( linea );
	}

	do {
		cout << "Documento de identidad: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	tripulante.setDocumentoIdentidad( linea ); 

	do {
		cout << "Nombre: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	tripulante.setNombre( linea );

	do {
		cout << "Nacionalidad: ";
		getline( cin, linea );
		cout << ( linea == "" ? "Favor ingrese dato\n" : "" );
	} while( linea == "" );
	tripulante.setNacionalidad( linea );

	int rolOpcion;
	cout << "Rol (1: PILOTO, 2: COPILOTO, 3: AUXILIAR): ";
	cin >> rolOpcion;
	cin.ignore();
	tripulante.setRol( static_cast<Tripulante::Rol>( rolOpcion ) );

	switch( indice )
	{
		case -1: tripulantes.push_back( tripulante ); break;
		default: tripulantes[ indice ] = tripulante; break;
	}

	cout << "Accion realizada de manera " << ( guardarTripulantes( tripulantes ) ? "exitosa" : "erronea" ) << endl;
}


void realizarAccionTripulante( string accion = "ELIMINAR" )
{
	cout << accion << " TRIPULANTE" << endl;
	vector<Tripulante> tripulantes = listarTripulantes();
	
	if ( !tripulantes.empty() )
	{
		string codigo = "";
		bool encontrado = false;
		do {
			cout << "Digite el codigo del tripulante: ";
			getline( cin, codigo );
			cout << ( codigo == "" ? "Favor ingrese dato\n" : "" );
		}
		while( codigo == "" );

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
 * Submenu
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
		cout << "0) Regresar" << endl << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore(); // Limpiar el buffer de entrada

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