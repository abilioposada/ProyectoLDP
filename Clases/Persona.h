#pragma once

#include <iostream>
#include <string>    
#include <iomanip>  
#include <sstream>  

using namespace std;

class Persona
{
	private:
		string documentoIdentidad;
		string nombre;
		string nacionalidad;

	public:
		
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

		string getDocumentoIdentidad() const 
		{
			return this->documentoIdentidad;
		}

		void setDocumentoIdentidad( string documentoIdentidad ) 
		{
			this->documentoIdentidad = documentoIdentidad;
		}

		string getNombre() const
		{
			return this->nombre;
		}

		void setNombre( string nombre )
		{
			this->nombre = nombre;
		}

		string getNacionalidad() const
		{
			return this->nacionalidad;
		}

		void setNacionalidad( string nacionalidad )
		{
			this->nacionalidad = nacionalidad;
		}

		
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
				ss << left << setw(15) << documentoIdentidad
				   << left << setw(25) << nombre
				   << left << setw(20) << nacionalidad;
				return ss.str();
			} else {
				return this->documentoIdentidad + separador +
					   this->nombre + separador +
					   this->nacionalidad;
			}
		}
};