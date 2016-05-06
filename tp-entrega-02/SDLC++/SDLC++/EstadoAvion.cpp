#include "EstadoAvion.h"


EstadoAvion::EstadoAvion(int id, int frame, int posX, int posY) {

	this->id = id;
	this->frame = frame;
	this->x = posX;
	this->y = posY;
}

EstadoAvion::~EstadoAvion(void) {
}

int EstadoAvion::getId() {
	return id;
}

int EstadoAvion::getFrame() {
	return frame;
}

int EstadoAvion::getPosX() {
	return x;
}

int EstadoAvion::getPosY() {
	return y;
}