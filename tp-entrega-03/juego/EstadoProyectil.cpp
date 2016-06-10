#include "EstadoProyectil.h"

EstadoProyectil::EstadoProyectil(int frame, int posX, int posY) {

	this->frame = frame;
	this->x = posX;
	this->y = posY;
}

EstadoProyectil::EstadoProyectil() {
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

void EstadoProyectil::setFrame(int frame) {
	this->frame = frame;
}

void EstadoProyectil::setPosX(int x) {
	this->x = x;
}

void EstadoProyectil::setPosY(int y) {
	this->y = y;
}

int EstadoProyectil::getSizeBytes(){
	return(sizeof(int)*4);
}