#pragma once

#include <iostream>
#include <string>    
#include <iomanip>   
#include <sstream>   

#include "Persona.h"

using namespace std;

class Pasajero : public Persona
{
	public: enum class Estado { NOVALIDADO, VALIDADO }; // Cambiado el nombre de los estados para mejor legibilidad

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

		string getAsiento() const // Añadido 'const'
		{
			return this->asiento;
		}

		void setAsiento( string asiento )
		{
			this->asiento = asiento;
		}

		Estado getEstado() const 
		{
			return this->estado;
		}

		void setEstado( Estado estado = Estado::NOVALIDADO )
		{
			this->estado = estado;
		}

		
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
				ss << Persona::toString( separador, forDisplay )
				   << left << setw(10) << asiento; 

				string estadoStr;
				switch (estado) {
					case Estado::NOVALIDADO: estadoStr = "No Validado"; break;
					case Estado::VALIDADO: estadoStr = "Validado"; break;
				}
				ss << left << setw(15) << estadoStr; 
				return ss.str();
			} else {
				string cadena = Persona::toString( separador ); 
				cadena += separador + this->asiento;
				cadena += separador + to_string( static_cast<int>(this->estado) ); 
				return cadena;
			}
		}
};