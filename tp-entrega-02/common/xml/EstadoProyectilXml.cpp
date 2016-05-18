#include "EstadoProyectilXml.h"

EstadoProyectilXml::EstadoProyectilXml()
{
	this->sizeBytes = -1;
	this->frame = -1;
	this->posX = -1;
	this->posY = -1;
}

EstadoProyectilXml::EstadoProyectilXml(int frame,int posX, int posY){

	this->frame = frame;
	this->posX = posX;
	this->posY = posY;
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) ;
}

EstadoProyectilXml::~EstadoProyectilXml(){
}

void EstadoProyectilXml::setId(int id){
	id = id;
}
int EstadoProyectilXml::getId(){
	return -1;//this->id;
}

int EstadoProyectilXml::getSizeBytes(){
	return this->sizeBytes;
}

void EstadoProyectilXml::calculateSizeBytes(){
	this->sizeBytes =  sizeof(int) //sizeBytes
		+ sizeof(int) //frame
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}

void EstadoProyectilXml::setFrame(int frame){
	this->frame = frame;
}
int EstadoProyectilXml::getFrame(){
	return this->frame;
}

void EstadoProyectilXml::setPosX(int posX){
	this->posX = posX;
}

int EstadoProyectilXml::getPosX(){
	return this->posX;
}

void EstadoProyectilXml::setPosY(int posY){
	this->posY = posY;
}

int EstadoProyectilXml::getPosY(){
	return this->posY;
}

void EstadoProyectilXml::toString(TCadena1000 cadena){
	sprintf(cadena,"\n sizeBytes=%d,frame=%d,posX=%d,posY=%d", "EstadoProyectilXml:",sizeBytes,frame,posX, posY);
}