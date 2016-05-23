#include "Jugador.h"

Jugador::Jugador()
{
	this->idCliente = -1;
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

