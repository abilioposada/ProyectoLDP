#include <iostream>

void limpiarConsola();

#include "Modulos/Rutas.h"
#include "Modulos/Pasajeros.h"
#include "Modulos/Tripulantes.h"
#include "Modulos/Vuelos.h"
#include "Modulos/Reservas.h"

using namespace std;

int main()
{
	int opcion = 1;

	while( opcion != 0 )
	{
		limpiarConsola();
		cout << "MENU PRINCIPAL" << endl;
		cout << "1) Rutas" << endl;
		cout << "2) Pasajeros" << endl;
		cout << "3) Tripulantes" << endl;
		cout << "4) Vuelos" << endl;
		cout << "5) Reservas" << endl;
		cout << "0) Salir" << endl << endl;

		cout << "Elija opcion: ";
		cin >> opcion;
		cin.ignore();

		switch( opcion )
		{
			case 0: break;

			case 1:
				irModuloRutas();
				break;

			case 2:
				irModuloPasajeros();
				break;

			case 3:
				irModuloTripulantes();
				break;

			case 4:
				irModuloVuelos();
				break;

			case 5:
				irModuloReservas();
				break;

			default:
				cout << "No ha seleccionado una opcion valida" << endl << endl;
				break;
		}
	}

	cout << "Gracias por utilizarnos" << endl;
	getchar();

	return 0;
}


void limpiarConsola()
{
	#ifdef _WIN32
		system( "cls" );
	#else
		system( "clear" );
	#endif
}