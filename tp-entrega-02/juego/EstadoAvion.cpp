#include "EstadoAvion.h"

EstadoAvion::EstadoAvion(int id, int frame, int posX, int posY) {

	this->id = id;
	this->frame = frame;
	this->x = posX;
	this->y = posY;
}

EstadoAvion::~EstadoAvion(void) {
	std::list<EstadoProyectil*>::iterator it;
	for (it = estadosProyectiles.begin(); it != estadosProyectiles.end(); it++) {
		delete (*it);
	}
	estadosProyectiles.clear();
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

std::list<EstadoProyectil*> EstadoAvion::getEstadosProyectiles(){
	return this->estadosProyectiles;
}

void EstadoAvion::setId(int id) {
	this->id = id;
}

void EstadoAvion::setFrame(int frame) {
	this->frame = frame;
}

void EstadoAvion::setPosX(int posX) {
	this->x = posX;
}

void EstadoAvion::setPosY(int posY) {
	this->y = posY;
}

void EstadoAvion::agregarEstadoProyectil(EstadoProyectil* estadoProyectil){
	this->estadosProyectiles.push_back(estadoProyectil);
}

void EstadoAvion::setEstadoProyectiles(std::list<EstadoProyectil*> lista) {

	std::list<EstadoProyectil*>::iterator it;

	for (it = this->estadosProyectiles.begin(); it != this->estadosProyectiles.end(); it++) {
		delete (*it);
	}

	for (it = lista.begin(); it != lista.end(); it++) {
		this->estadosProyectiles.push_back(*it);
	}
}