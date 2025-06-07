#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Ruta.h"
#include "Tripulacion.h"

using namespace std;

class Vuelo
{
	private:
		string codigo;
		string fechaHoraSalida;
		string fechaHoraLlegada;
		int capacidad;
		string tipoAvion;
		Ruta ruta;
		vector<Tripulacion> tripulantes;

	public:
		/**
		 * Constructor con parámetros por defecto
		 */
		Vuelo(
			string codigo = "",
			string fechaHoraSalida = "",
			string fechaHoraLlegada = "",
			int capacidad = 0,
			string tipoAvion = "",
			Ruta ruta = Ruta(),
			vector<Tripulacion> tripulantes = {}
		) {
			this->codigo = codigo;
			this->fechaHoraSalida = fechaHoraSalida;
			this->fechaHoraLlegada = fechaHoraLlegada;
			this->capacidad = capacidad;
			this->tipoAvion = tipoAvion;
			this->ruta = ruta;
			this->tripulantes = tripulantes;
		}

		/**
		 * Destructor
		 */
		~Vuelo() {}

		// Getters & setters
		string getCodigo()
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		string getFechaHoraSalida()
		{
			return this->fechaHoraSalida;
		}

		void setFechaHoraSalida( string fechaHoraSalida )
		{
			this->fechaHoraSalida = fechaHoraSalida;
		}

		string getFechaHoraLlegada()
		{
			return this->fechaHoraLlegada;
		}

		void setFechaHoraLlegada( string fechaHoraLlegada )
		{
			this->fechaHoraLlegada = fechaHoraLlegada;
		}

		int getCapacidad()
		{
			return this->capacidad;
		}

		void setCapacidad( int capacidad )
		{
			this->capacidad = capacidad;
		}

		string getTipoAvion()
		{
			return this->tipoAvion;
		}

		void setTipoAvion( string tipoAvion )
		{
			this->tipoAvion = tipoAvion;
		}

		Ruta getRuta()
		{
			return this->ruta;
		}

		void setRuta( Ruta ruta )
		{
			this->ruta = ruta;
		}

		vector<Tripulacion> getTripulantes()
		{
			return this->tripulantes;
		}

		void setTripulantes( vector<Tripulacion> tripulantes )
		{
			this->tripulantes = tripulantes;
		}

		/**
		 * Convierte el objeto a cadena de caracteres
		 */
		string toString( char separador = ' ' )
		{
			return this->getCodigo() + separador +
				this->getFechaHoraSalida() + separador +
				this->getFechaHoraLlegada() + separador +
				to_string( this->getCapacidad() ) + separador +
				this->getTipoAvion() + separador +
				this->getRuta().toString();
		}
};
