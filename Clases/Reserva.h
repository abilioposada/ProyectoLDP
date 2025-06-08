#pragma once

#include <iostream>
#include <string>   
#include <iomanip>   
#include <sstream>   

#include "Vuelo.h"
#include "Pasajero.h"

using namespace std;

class Reserva
{
	public: enum class Estado { ADEUDADO, PAGADO };

	private:
		string numero;
		string fechaHora;
		Estado estado;
		Vuelo vuelo;
		Pasajero pasajero;

	public:
		
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

		string getNumero() const
		{
			return this->numero;
		}

		void setNumero( string numero )
		{
			this->numero = numero;
		}

		string getFechaHora() const
		{
			return this->fechaHora;
		}

		void setFechaHora( string fechaHora )
		{
			this->fechaHora = fechaHora;
		}

		Estado getEstado() const
		{
			return this->estado;
		}

		void setEstado( Estado estado = Estado::ADEUDADO )
		{
			this->estado = estado;
		}

		Vuelo getVuelo() const // Añadido 'const'
		{
			return this->vuelo;
		}

		void setVuelo( Vuelo vuelo )
		{
			this->vuelo = vuelo;
		}

		Pasajero getPasajero() const // Añadido 'const'
		{
			return this->pasajero;
		}

		void setPasajero( Pasajero pasajero )
		{
			this->pasajero = pasajero;
		}

	
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
				ss << left << setw(10) << numero           
				   << left << setw(20) << fechaHora;      

				string estadoStr;
				switch (estado) {
					case Estado::ADEUDADO: estadoStr = "Adeudado"; break;
					case Estado::PAGADO: estadoStr = "Pagado"; break;
				}
				ss << left << setw(15) << estadoStr
				   << left << setw(10) << vuelo.getCodigo()           
				   << left << setw(15) << pasajero.getDocumentoIdentidad(); 
				return ss.str();
			} else {
				return this->numero + separador +
					   this->fechaHora + separador +
					   to_string( static_cast<int>(this->estado) ) + separador +
					   this->vuelo.getCodigo() + separador + 
					   this->pasajero.getDocumentoIdentidad();
			}
		}
};