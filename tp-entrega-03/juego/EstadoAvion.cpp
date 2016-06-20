#include "EstadoAvion.h"

EstadoAvion::EstadoAvion() {

	this->sizeBytes = -1;
	this->id = -1;
	this->frame = -1;
	this->posX = -1;
	this->posY = -1;
}
EstadoAvion::EstadoAvion(int id, int frame, int posX, int posY) {
	this->sizeBytes = -1;
	this->id = id;
	this->frame = frame;
	this->posX = posX;
	this->posY = posY;
}

EstadoAvion::~EstadoAvion(void) {
	std::list<EstadoProyectil*>::iterator it;
	for (it = estadosProyectiles.begin(); it != estadosProyectiles.end(); it++) {
		delete (*it);
	}
	estadosProyectiles.clear();
}

int EstadoAvion::getSizeBytes(){
	int tamanioTotal = 
	     sizeof(int) //sizeBytes
		+ sizeof(int)  //id
		+ sizeof(int) //frame
		+ sizeof(int) //posX
		+ sizeof(int); //posY
	return tamanioTotal;
}

void EstadoAvion::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)  //id
		+ sizeof(int) //frame
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}


void EstadoAvion::setId(int id) {
	this->id = id;
}

int EstadoAvion::getId() {
	return id;
}
void EstadoAvion::setFrame(int frame) {
	this->frame = frame;
}

int EstadoAvion::getFrame() {
	return this->frame;
}

void EstadoAvion::setPosX(int posX) {
	this->posX = posX;
}

int EstadoAvion::getPosX() {
	return this->posX;
}

void EstadoAvion::setPosY(int posY) {
	this->posY = posY;
}

int EstadoAvion::getPosY() {
	return this->posY;
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

std::list<EstadoProyectil*> EstadoAvion::getEstadosProyectiles(){
	return this->estadosProyectiles;
}

