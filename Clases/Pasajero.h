#pragma once

#include <iostream>
#include <fstream>

#include "Persona.h"

using namespace std;

class Pasajero : public Persona
{
	enum class Estado { NOVALIDADO, VALIDADO };

	private:
		string asiento;
		Estado estado;

	public:
		/**
		 * Constructor con parámetros por defecto
		 */
		Pasajero(
			string documentoIdentidad = "",
			string nombre = "",
			string nacionalidad = "",
			string asiento = "",
			Estado estado = Estado::NOVALIDADO
		)
			: Persona( documentoIdentidad, nombre, nacionalidad )
		{
			this->asiento = asiento;
			this->estado = estado;
		}

		/**
		 * Destructor
		 */
		~Pasajero() {}
		
		// Getters & setters
		string getAsiento()
		{
			return this->asiento;
		}

		void setAsiento( string asiento )
		{
			this->asiento = asiento;
		}

		Estado getEstado()
		{
			return this->estado;
		}

		void setEstado( Estado estado )
		{
			this->estado = estado;
		}

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString()
		{
			return Persona::toString() + " " + this->getAsiento() + " " + ( this->getEstado() == Estado::VALIDADO ? "Validado" : "No validado" );
		}
};
