#include "Posicion.h"

Posicion::Posicion(int x, int y) {
    this->x = x;
    this->y = y;
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int);
}

Posicion::Posicion() {
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int);
}

Posicion::~Posicion() {
}

int Posicion::getPosX() {
    return this->x;
}

int Posicion::getPosY() {
    return this->y;
}

void Posicion::setPosX(int x) {
	this->x = x;
}

void Posicion::setPosY(int y) {
	this->y = y;
}

int Posicion::getSizeBytes() {
	return this->sizeBytes;
}

void Posicion::calculateSizeBytes() {
	this->sizeBytes =  sizeof(int) //sizeBytes
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}
void Posicion::toString(TCadena1000 cadena){
	sprintf(cadena,"Posicion:x=%d,y=%d",x,y);
}