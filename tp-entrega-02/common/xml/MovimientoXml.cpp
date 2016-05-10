#include "MovimientoXml.h"

MovimientoXml::MovimientoXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->tipo = -1;
	this->posX = -1;
	this->posY = -1;
}

MovimientoXml::MovimientoXml(int id,int tipo,int posX, int posY){

	this->id = id;
	this->tipo = tipo;
	this->posX = posX;
	this->posY = posY;
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) ;
}

MovimientoXml::~MovimientoXml(){
}

int MovimientoXml::getSizeBytes(){
	return this->sizeBytes;
}

void MovimientoXml::calculateSizeBytes(){
	this->sizeBytes =  sizeof(int) //sizeBytes
		+ sizeof(int)  //id
		+ sizeof(int) //tipo
		+ sizeof(int) //posX
		+ sizeof(int); //posY
}

void MovimientoXml::setId(int id){
	this->id = id;
}
int MovimientoXml::getId(){
	return this->id;
}
void MovimientoXml::setTipo(int tipo){
	this->tipo = tipo;
}
int MovimientoXml::getTipo(){
	return this->tipo;
}

void MovimientoXml::setPosX(int posX){
	this->posX = posX;
}

int MovimientoXml::getPosX(){
	return this->posX;
}

void MovimientoXml::setPosY(int posY){
	this->posY = posY;
}

int MovimientoXml::getPosY(){
	return this->posY;
}

void MovimientoXml::toString(TCadena1000 cadena){
	sprintf(cadena,"\n% sizeBytes=%d,id=%d,tipo=%d,posX=%d,posY=%d", "MovimientoXml:",sizeBytes,id,tipo,posX, posY);
}