#pragma once

#include <iostream>
#include <string>   
#include <iomanip>   
#include <sstream>   

#include "Persona.h"

using namespace std;

class Tripulante : public Persona
{
	public: enum class Rol { PILOTO = 1, COPILOTO = 2, AUXILIAR = 3 };

	private:
		string codigo;
		Rol rol;

	public:
		/**
		 * Constructor
		 */
		Tripulante(
			string documentoIdentidad = "", 
			string nombre = "",
			string nacionalidad = "",
			string codigo = "",
			Rol rol = Rol::AUXILIAR
		)
			: Persona( documentoIdentidad, nombre, nacionalidad )
		{
			this->codigo = codigo;
			this->rol = rol;
		}

		/**
		 * Destructor
		 */
		~Tripulante() {}

		string getCodigo() const // Añadido 'const'
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		Rol getRol() const // Añadido 'const'
		{
			return this->rol;
		}

		void setRol( Rol rol = Tripulante::Rol::AUXILIAR )
		{
			this->rol = rol;
		}

		

		
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
			
				ss << Persona::toString( separador, forDisplay )
				   << left << setw(10) << codigo; 

				string rolStr;
				switch (rol) {
					case Rol::PILOTO: rolStr = "Piloto"; break;
					case Rol::COPILOTO: rolStr = "Copiloto"; break;
					case Rol::AUXILIAR: rolStr = "Auxiliar"; break;
				}
				ss << left << setw(15) << rolStr; // Ancho para rol
				return ss.str();
			} else {
				string cadena = Persona::toString( separador ); 
				cadena += separador + this->codigo;
				cadena += separador + to_string( static_cast<int>(this->rol) ); 
				return cadena;
			}
		}
};