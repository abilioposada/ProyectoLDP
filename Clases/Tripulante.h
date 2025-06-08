#pragma once

#include <iostream>
// #include <vector>

#include "Persona.h"
// #include "Vuelo.h"

using namespace std;

class Tripulante : public Persona
{
	public: enum class Rol { PILOTO = 1, COPILOTO = 2, AUXILIAR = 3 };

	private:
		string codigo;
		string nombre;
		Rol rol;
		// vector<Vuelo> vuelos;

	public:
		/**
		 * Constructor
		 */
		Tripulante(
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
		~Tripulante() {}
		
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

		void setRol( Rol rol = Tripulante::Rol::AUXILIAR )
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
		string toString( string separador = " ", bool amigable = true )
		{
			return this->getCodigo() + separador +
				Persona::toString( separador ) + separador +
				( amigable ?
					( this->getRol() == Rol::AUXILIAR ? "Auxiliar" :
						(
							this->getRol() == Rol::PILOTO ? "Piloto" : "Copiloto"
						)
					) :
					to_string( static_cast<int>( this->getRol() ) )
				);
		}
};
