#pragma once

#include <iostream>

#include "Persona.h"

using namespace std;

class Pasajero : public Persona
{
	public: enum class Estado { NOVALIDADO, VALIDADO };

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
		string toString( char separador = ' ', bool amigable = true )
		{
			return Persona::toString( separador ) + separador +
				this->getAsiento() + separador +
				( amigable ?
					( this->getEstado() == Estado::VALIDADO ? "Validado" : "No validado" ) :
					to_string( static_cast<int>( this->getEstado() ) )
				);
		}
};
