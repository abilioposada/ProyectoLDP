#pragma once

#include <iostream>

using namespace std;

class Persona
{
	private:
		string documentoIdentidad;
		string nombre;
		string nacionalidad;

	public:
		/**
		 * Constructor con parámetros por defecto
		 */
		Persona( string documentoIdentidad = "", string nombre = "", string nacionalidad = "" )
		{
			this->documentoIdentidad = documentoIdentidad;
			this->nombre = nombre;
			this->nacionalidad = nacionalidad;
		}

		/**
		 * Destructor
		 */
		~Persona() {}

		string getDoucmentoIdentidad()
		{
			return this->documentoIdentidad;
		}

		void setDoucumentoIdentidad( string documentoIdentidad )
		{
			this->documentoIdentidad = documentoIdentidad;
		}

		string getNombre()
		{
			return this->nombre;
		}

		void setNombre( string nombre )
		{
			this->nombre = nombre;
		}

		string getNacionalidad()
		{
			return this->nacionalidad;
		}

		void setNacionalidad( string nacionalidad )
		{
			this->nacionalidad = nacionalidad;
		}

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString( string separador = " " )
		{
			return this->getDoucmentoIdentidad() + separador +
				this->getNombre() + separador +
				this->getNacionalidad();
		}
};
