#include "Jugador.h"

Jugador::Jugador()
{
	this->idCliente = -1;
	this->nombreDeUsuario.assign("");
}

Jugador::~Jugador()
{
}

void Jugador::setIdCliente(int idCliente){
	this->idCliente = idCliente;
}

int Jugador::getIdCliente(){
	return this->idCliente;
}

void Jugador::setPosicionAvion(Posicion pos) {
	this->poscion = pos;
}

Posicion Jugador::getPosicion() {
	return this->poscion;
}