#include "EstadoJugador.h"


EstadoJugador::EstadoJugador(int id, int puntajeAcumulado, int equipo){
	this->id = id;
	this->puntajeAcumulado = puntajeAcumulado;
	this->equipo = equipo;
}
EstadoJugador::EstadoJugador(){
	this->id = -1;
	this->puntajeAcumulado = -1;
	this->equipo = -1;
}

int EstadoJugador::getid(){
	return id;
}

int EstadoJugador::getPuntajeAcumulado(){
	return puntajeAcumulado;
}

int EstadoJugador::getEquipo() {
	return this->equipo;
}

EstadoJugador::~EstadoJugador(void){
}

void EstadoJugador::toString(TCadena1000 cadena){
	sprintf(cadena,"\nEstadoJugador: id=%d,puntajeAcumulado=%d,equipo=%d",id,puntajeAcumulado, equipo);
}