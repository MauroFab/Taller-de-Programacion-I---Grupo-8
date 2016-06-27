#include "Temporizador.h"

Temporizador::Temporizador() {
	this->contadorTiempo = 0;
	this->baseDeTiempo = 0.007;
}

Temporizador::Temporizador(int segundos) {
	this->tiempoEstablecido = segundos;
	this->contadorTiempo = 0;
	this->baseDeTiempo = 0.007;
	this->cantidadIteraciones = segundos/this->baseDeTiempo;
}

Temporizador::~Temporizador(void) {
}

void Temporizador::setTiempo(int segundos) {
	this->tiempoEstablecido = segundos;
}

int Temporizador::getTiempo() {
	return this->tiempoEstablecido;
}

void Temporizador::avanzarTiempo() {
	this->contadorTiempo++;
}

void Temporizador::resetear() {
	this->contadorTiempo = 0;
}

bool Temporizador::pasoElTiempoEstablecido() {
	return (this->contadorTiempo/this->cantidadIteraciones);	
}