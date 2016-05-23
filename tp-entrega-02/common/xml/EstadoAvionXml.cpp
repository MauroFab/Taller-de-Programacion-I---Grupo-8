#include "EstadoAvionXml.h"

EstadoAvionXml::EstadoAvionXml()
{
	this->sizeBytes = Mensaje::getSizeBytes();
	this->id = -1;
	this->frame = -1;
	this->posX = -1;
	this->posY = -1;
}

EstadoAvionXml::EstadoAvionXml(int id,int frame,int posX, int posY){
	this->id = id;
	this->frame = frame;
	this->posX = posX;
	this->posY = posY;
	this->sizeBytes = Mensaje::getSizeBytes() + sizeof(int) + sizeof(int) + sizeof(int) ;
}

EstadoAvionXml::~EstadoAvionXml(){

	eliminarProyectiles();

}

int EstadoAvionXml::getSizeBytes(){
	return this->sizeBytes;
}

void EstadoAvionXml::calculateSizeBytes(){
	this->sizeBytes =  Mensaje::getSizeBytes()
		+ sizeof(int) //frame
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}

int EstadoAvionXml::getTipo(){
	return MENSAJE_ESTADO_AVION;
}

void EstadoAvionXml::setId(int id){
	this->id = id;
}
int EstadoAvionXml::getId(){
	return this->id;
}
void EstadoAvionXml::setFrame(int frame){
	this->frame = frame;
}
int EstadoAvionXml::getFrame(){
	return this->frame;
}

void EstadoAvionXml::setPosX(int posX){
	this->posX = posX;
}

int EstadoAvionXml::getPosX(){
	return this->posX;
}

void EstadoAvionXml::setPosY(int posY){
	this->posY = posY;
}

int EstadoAvionXml::getPosY(){
	return this->posY;
}

void EstadoAvionXml::agregarEstadoProyectil(EstadoProyectilXml* estadoProyectil){
	this->estadosProyectiles.push_back(estadoProyectil);
}


//si van a usar esto, referirse a la nota en el header.
void EstadoAvionXml::liberarMemoriaProyectiles(){
	std::list<EstadoProyectilXml*>::iterator it;
	for (it = estadosProyectiles.begin(); it != estadosProyectiles.end(); it++) {
		delete (*it);
	}
	eliminarProyectiles();
}

void EstadoAvionXml::eliminarProyectiles(){
	estadosProyectiles.clear();
}

list<EstadoProyectilXml*> EstadoAvionXml::getEstadosProyectiles(){
	return this->estadosProyectiles;
}

void EstadoAvionXml::toString(TCadena1000 cadena){
	sprintf(cadena,"\n% sizeBytes=%d,id=%d,frame=%d,posX=%d,posY=%d", "MovimientoXml:",sizeBytes,id,frame,posX, posY);
}