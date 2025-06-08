#pragma once

#include <iostream>

#include "Vuelo.h"
#include "Pasajero.h"

using namespace std;

class Reserva
{
	enum class Estado { ADEUDADO, PAGADO };

	private:
		string numero;
		string fechaHora;
		Estado estado;
		Vuelo vuelo;
		Pasajero pasajero;

	public:
		/**
		 * Constructor con parámetros por defecto
		 */
		Reserva(
			string numero = "",
			string fechaHora = "",
			Estado estado = Estado::ADEUDADO,
			Vuelo vuelo = Vuelo(),
			Pasajero pasajero = Pasajero()
		) {
			this->numero = numero;
			this->fechaHora = fechaHora;
			this->estado = estado;
			this->vuelo = vuelo;
			this->pasajero = pasajero;
		}

		/**
		 * Destructor
		 */
		~Reserva() {}

		// Getters & setters
		string getNumero()
		{
			return this->numero;
		}

		void setNumero( string numero )
		{
			this->numero = numero;
		}

		string getFechaHora()
		{
			return this->fechaHora;
		}

		void setFechaHora( string fechaHora )
		{
			this->fechaHora = fechaHora;
		}

		Estado getEstado()
		{
			return this->estado;
		}

		void setEstado( Estado estado )
		{
			this->estado = estado;
		}

		Vuelo getVuelo()
		{
			return this->vuelo;
		}

		void setVuelo( Vuelo vuelo )
		{
			this->vuelo = vuelo;
		}

		Pasajero getPasajero()
		{
			return this->pasajero;
		}

		void setPasajero( Pasajero pasajero )
		{
			this->pasajero = pasajero;
		}

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString( string separador = " " )
		{
			return this->getNumero() + separador +
				this->getFechaHora() + separador +
				to_string( static_cast<int> ( this->getEstado() ) ) + separador +
				this->getVuelo().toString( separador ) + separador +
				this->getPasajero().toString( separador );
		}
};
