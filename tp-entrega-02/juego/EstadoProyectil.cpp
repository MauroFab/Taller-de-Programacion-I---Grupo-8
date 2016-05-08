#include "EstadoProyectil.h"

EstadoProyectil::EstadoProyectil(int frame, int posX, int posY) {

	this->frame = frame;
	this->x = posX;
	this->y = posY;
}

EstadoProyectil::~EstadoProyectil(void) {
}

int EstadoProyectil::getFrame() {
	return frame;
}

int EstadoProyectil::getPosX() {
	return x;
}

int EstadoProyectil::getPosY() {
	return y;
}