#include "EstadoProyectil.h"
EstadoProyectil::EstadoProyectil(){
	this->sizeBytes = -1;
	this->frame = -1;
	this->posX = -1;
	this->posY = -1;
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) ;	
}
EstadoProyectil::EstadoProyectil(int frame, int posX, int posY, bool estaMejorado, bool visible) {

	this->sizeBytes = -1;
	this->frame = frame;
	this->posX = posX;
	this->posY = posY;
	this->mejorado = estaMejorado;
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) ;
	this->visible = visible;
}

EstadoProyectil::~EstadoProyectil(void) {
}

void EstadoProyectil::setId(int id){
	
}
int EstadoProyectil::getId(){
	return -1;
}

int EstadoProyectil::getSizeBytes(){
	return this->sizeBytes;
}

void EstadoProyectil::calculateSizeBytes(){
	this->sizeBytes =  sizeof(int) //sizeBytes
		+ sizeof(int) //frame
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}

void EstadoProyectil::setFrame(int frame) {
	this->frame = frame;
}

int EstadoProyectil::getFrame() {
	return this->frame;
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

void EstadoProyectil::toString(TCadena1000 cadena){
	sprintf(cadena,"\nEstadoProyectil: sizeBytes=%d,frame=%d,posX=%d,posY=%d", sizeBytes,frame,posX, posY);
}

void EstadoProyectil::setMejorado(bool mejorado){
	this->mejorado = mejorado;
}

bool EstadoProyectil::getMejorado(){
	return mejorado;
}

bool EstadoProyectil::getVisible(){
	return visible;
}

void EstadoProyectil::setVisible(bool visible){
	this->visible = visible;
}