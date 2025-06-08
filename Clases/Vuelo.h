#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> 
#include <sstream>   

#include "Ruta.h"
#include "Tripulante.h"

using namespace std;

class Vuelo
{
	private:
		string codigo;
		string fechaHoraSalida;
		string fechaHoraLlegada;
		int capacidad;
		string tipoAvion;
		Ruta ruta; // Objeto Ruta
		vector<Tripulante> tripulantes; 

	public:
		
		Vuelo(
			string codigo = "",
			string fechaHoraSalida = "",
			string fechaHoraLlegada = "",
			int capacidad = 0,
			string tipoAvion = "",
			Ruta ruta = Ruta(),
			vector<Tripulante> tripulantes = {}
		) {
			this->codigo = codigo;
			this->fechaHoraSalida = fechaHoraSalida;
			this->fechaHoraLlegada = fechaHoraLlegada;
			this->capacidad = capacidad;
			this->tipoAvion = tipoAvion;
			this->ruta = ruta;
			this->tripulantes = tripulantes;
		}

		
		~Vuelo() {}

		string getCodigo() const
		{
			return this->codigo;
		}

		void setCodigo( string codigo )
		{
			this->codigo = codigo;
		}

		string getFechaHoraSalida() const
		{
			return this->fechaHoraSalida;
		}

		void setFechaHoraSalida( string fechaHoraSalida )
		{
			this->fechaHoraSalida = fechaHoraSalida;
		}

		string getFechaHoraLlegada() const
		{
			return this->fechaHoraLlegada;
		}

		void setFechaHoraLlegada( string fechaHoraLlegada )
		{
			this->fechaHoraLlegada = fechaHoraLlegada;
		}

		int getCapacidad() const
		{
			return this->capacidad;
		}

		void setCapacidad( int capacidad )
		{
			this->capacidad = capacidad;
		}

		string getTipoAvion() const
		{
			return this->tipoAvion;
		}

		void setTipoAvion( string tipoAvion )
		{
			this->tipoAvion = tipoAvion;
		}

		Ruta getRuta() const 
		{
			return this->ruta;
		}

		void setRuta( Ruta ruta )
		{
			this->ruta = ruta;
		}

		vector<Tripulante> getTripulantes() const
		{
			return this->tripulantes;
		}

		void setTripulantes( vector<Tripulante> tripulantes )
		{
			this->tripulantes = tripulantes;
		}

		
		string toString( string separador = " ", bool forDisplay = false ) const
		{
			if (forDisplay) {
				stringstream ss;
				ss << left << setw(10) << codigo           // Ancho para codigo
				   << left << setw(20) << fechaHoraSalida  // Ancho para fecha/hora salida
				   << left << setw(20) << fechaHoraLlegada // Ancho para fecha/hora llegada
				   << right << setw(10) << capacidad       // Ancho para capacidad (alineado a la derecha)
				   << left << setw(15) << tipoAvion        // Ancho para tipo de avión
				   << left << setw(10) << ruta.getCodigo(); // Solo el codigo de la ruta para display
				
				return ss.str();
			} else {
				string tripulantesStr = "";
				for ( const Tripulante& t : this->tripulantes ) {
					tripulantesStr += t.getCodigo() + ","; 
				}
				if (!tripulantesStr.empty()) {
					tripulantesStr.pop_back();
				}

				return this->codigo + separador +
					   this->fechaHoraSalida + separador +
					   this->fechaHoraLlegada + separador +
					   to_string( this->capacidad ) + separador +
					   this->tipoAvion + separador +
					   this->ruta.getCodigo() + separador + 
					   tripulantesStr;
			}
		}
};