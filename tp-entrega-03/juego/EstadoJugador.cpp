#include "EstadoJugador.h"


EstadoJugador::EstadoJugador(int id, int puntajeAcumulado, int equipo, string nommbre){
	this->id = id;
	this->puntajeAcumulado = puntajeAcumulado;
	this->equipo = equipo;
	this->nombre = nombre;
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

string EstadoJugador::getNombreUsuario() {
	return this->nombre;
}

EstadoJugador::~EstadoJugador(void){
}

void EstadoJugador::toString(TCadena1000 cadena){
	sprintf(cadena,"\nEstadoJugador: id=%d,puntajeAcumulado=%d,equipo=%d,nombreDeUsuario=%s",id,puntajeAcumulado, equipo, nombre.c_str());
}