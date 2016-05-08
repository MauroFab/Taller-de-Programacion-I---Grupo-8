#include "Movimiento.h"

Movimiento::Movimiento(int id, int tipo, int posX, int posY) {

	this->id = id;
	this->tipo = tipo;
	this->x = posX;
	this->y = posY;
}

Movimiento::~Movimiento() {
}

int Movimiento::getId() {
	return id;
}

int Movimiento::getTipo() {
	return tipo;
}

int Movimiento::getPosX() {
	return x;
}

int Movimiento::getPosY() {
	return y;
}