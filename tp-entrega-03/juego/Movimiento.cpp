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

void Movimiento::setId(int id) {
	this->id = id;
}

void Movimiento::setTipo(int tipo) {
	this->tipo = tipo;
}

void Movimiento::setPosX(int posX) {
	this->x = posX;
}

void Movimiento::setPosY(int posY) {
	this->y = posY;
}