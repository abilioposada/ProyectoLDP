#pragma once

#include <iostream>
#include <string>
#include <iomanip>  
#include <sstream>  

using namespace std;

class Ruta
{
	private:
		string codigo;
		string origen;
		string destino;
		int duracion; // Minutos
		float tarifa;

	public:
		/**
		 * Constructor con parámetros por defecto
		 */
		Ruta( string codigo = "", string origen = "", string destino = "", int duracion = 0, float tarifa = 0.0 )
		{
			this->codigo = codigo;
			this->origen = origen;
			this->destino = destino;
			this->duracion = duracion;
			this->tarifa = tarifa;
		}

		/**
		 * Destructor
		 */
		~Ruta() {}

		string getCodigo() const
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		string getOrigen() const
		{
			return this->origen;
		}

		void setOrigen( string origen )
		{
			this->origen = origen;
		}

		string getDestino() const
		{
			return this->destino;
		}

		void setDestino( string destino )
		{
			this->destino = destino;
		}

		int getDuracion() const
		{
			return this->duracion;
		}

		void setDuracion( int duracion )
		{
			this->duracion = duracion;
		}

		float getTarifa() const
		{
			return this->tarifa;
		}

		void setTarifa( float tarifa )
		{
			this->tarifa = tarifa;
		}

		
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
				ss << left << setw(10) << codigo           
				   << left << setw(15) << origen          
				   << left << setw(15) << destino          
				   << right << setw(10) << duracion      
				   << right << setw(10) << fixed << setprecision(2) << tarifa;
				return ss.str();
			} else {
				return this->codigo + separador +
					   this->origen + separador +
					   this->destino + separador +
					   to_string( this->duracion ) + separador +
					   to_string( this->tarifa );
			}
		}
};