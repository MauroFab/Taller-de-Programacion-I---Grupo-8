#include "EstadoJugador.h"


EstadoJugador::EstadoJugador(int id, int puntajeAcumulado){
	this->id = id;
	this->puntajeAcumulado = puntajeAcumulado;
}
EstadoJugador::EstadoJugador(){
	this->id = -1;
	this->puntajeAcumulado = -1;
}

int EstadoJugador::getid(){
	return id;
}

int EstadoJugador::getPuntajeAcumulado(){
	return puntajeAcumulado;
}

EstadoJugador::~EstadoJugador(void){
}

void EstadoJugador::toString(TCadena1000 cadena){
	sprintf(cadena,"\nEstadoJugador: id=%d,puntajeAcumulado=%d,",id,puntajeAcumulado);
}