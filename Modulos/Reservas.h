#pragma once

#include <iostream>

using namespace std;

void irModuloReservas()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		cout << "MODULO RESERVAS" << endl;
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
				break;
				
			case 2:
				break;
				
			case 3:
				break;
				
			default:
				cout << "No ha seleccionado opcion valida" << endl << endl;
				break;
		}
	}
}
