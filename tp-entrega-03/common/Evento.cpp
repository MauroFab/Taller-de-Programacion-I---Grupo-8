#include "Evento.h"

Evento::Evento(int numeroDeEvento){
	this->numeroDeEvento = numeroDeEvento;
}

int Evento::getNumeroDeEvento(){
	return numeroDeEvento;
}

void Evento::setNumeroDeEvento(int numero){
	numeroDeEvento = numero;
}

int Evento::getSizeBytes(){
	return (sizeof(int));
}
void Evento::toString(TCadena1000 cadena){
}

Evento::~Evento(){
}
