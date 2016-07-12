#pragma once

#include "../common/IGenericaVO.h"
#include <string>
#include <stdio.h>

using namespace std;

class EstadoJugador {

public:
	EstadoJugador(int id, int puntajeAcumulado, int equipo, string nombre);
	
	EstadoJugador(const EstadoJugador& e):id(e.id),puntajeAcumulado(e.puntajeAcumulado),
	equipo(e.equipo),nombre(e.nombre){};
	void EstadoJugador::operator=(const EstadoJugador &e){this->id=e.id; this->puntajeAcumulado=e.puntajeAcumulado;
	this->equipo=e.equipo;this->nombre=e.nombre;};
	
	//No usar este constructor por fuera del protocolo
	EstadoJugador();

	~EstadoJugador(void);
	int getid();
	int getPuntajeAcumulado();
	int getEquipo();
	string getNombreUsuario();
	void toString(TCadena1000 cadena);

private:
	int id;
	int puntajeAcumulado;
	int equipo;
	string nombre;
};

