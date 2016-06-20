#include "EstadoProyectil.h"

EstadoProyectil::EstadoProyectil(int frame, int posX, int posY) {

	this->frame = frame;
	this->posX = posX;
	this->posY = posY;
}

EstadoProyectil::EstadoProyectil() {
}

EstadoProyectil::~EstadoProyectil(void) {
}

int EstadoProyectil::getFrame() {
	return frame;
}

int EstadoProyectil::getSizeBytes(){
	return(sizeof(int)*4);
}


void EstadoProyectil::setFrame(int frame) {
	this->frame = frame;
}

void EstadoProyectil::setPosX(int posX) {
	this->posX = posX;
}
int EstadoProyectil::getPosX() {
	return this->posX;
}
void EstadoProyectil::setPosY(int posY) {
	this->posY = posY;
}

int EstadoProyectil::getPosY() {
	return this->posY;
}

