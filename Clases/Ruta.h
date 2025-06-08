#pragma once

#include <iostream>

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

		// Getters & setters
		string getCodigo()
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		string getOrigen()
		{
			return this->origen;
		}

		void setOrigen( string origen )
		{
			this->origen = origen;
		}

		string getDestino()
		{
			return this->destino;
		}

		void setDestino( string destino )
		{
			this->destino = destino;
		}

		int getDuracion()
		{
			return this->duracion;
		}

		void setDuracion( int duracion )
		{
			this->duracion = duracion;
		}

		float getTarifa()
		{
			return this->tarifa;
		}

		void setTarifa( float tarifa )
		{
			this->tarifa = tarifa;
		}

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString( string separador = " " )
		{
			return this->getCodigo() + separador +
				this->getOrigen() + separador +
				this->getDestino() + separador +
				to_string( this->getDuracion() ) + separador +
				to_string( this->getTarifa() );
		}
};
