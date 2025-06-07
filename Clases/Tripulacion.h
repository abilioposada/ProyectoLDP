#pragma once

#include <iostream>
// #include <vector>

#include "Persona.h"
// #include "Vuelo.h"

using namespace std;

class Tripulacion : public Persona
{
	enum class Rol { AUXILIAR, PILOTO, COPILOTO, SOBRECARGO };

	private:
		string codigo;
		string nombre;
		Rol rol;
		// vector<Vuelo> vuelos;

	public:
		/**
		 * Constructor
		 */
		Tripulacion(
			string doucmentoIdentidad = "",
			string nombre = "",
			string nacionalidad = "",
			string codigo = "",
			Rol rol = Rol::AUXILIAR/* ,
			vector<Vuelo> vuelos = {} */
		)
			: Persona( doucmentoIdentidad, nombre, nacionalidad )
		{
			this->codigo = codigo;
			this->rol = rol;
			// this->vuelos = vuelos;
		}

		/**
		 * Destructor
		 */
		~Tripulacion() {}
		
		// Getters & setters
		string getCodigo()
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		Rol getRol()
		{
			return this->rol;
		}

		void setRol( Rol rol )
		{
			this->rol = rol;
		}

		/* vector<Vuelo> getVuelos()
		{
			return this->vuelos;
		}

		void setVuelos( vector<Vuelo> vuelos )
		{
			this->vuelos = vuelos;
		} */

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString( char separador = ' ' )
		{
			return this->getCodigo() + separador +
				Persona::toString( separador ) + separador +
				to_string( static_cast<int>( this->getRol() ) );
		}
};
