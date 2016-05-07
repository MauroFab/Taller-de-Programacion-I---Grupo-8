#include "ServidorXml.h"
/* @autor sabris
 */
ServidorXml::ServidorXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->cantidadMaximaClientes = -1;
	this->puerto = -1;
//	VentanaXml ventanaXml;
//	EscenarioXml escenarioXml;
	for (int i = 0; i < MAX_SPRITES; i++){
		this->listaSprite[i] = NULL;
	}
	this->canSprs = 0;
	for (int i = 0; i < MAX_AVIONES; i++){
		this->listaAviones[i] = NULL;
	}
	this->canAvs = 0;
}

ServidorXml::~ServidorXml()
{
	for (int i = 0; i < MAX_SPRITES; i++){
		if (this->listaSprite[i] != NULL)
			delete this->listaSprite[i];
	}
	for (int i = 0; i < MAX_AVIONES; i++){
		if (this->listaAviones[i] != NULL)
			delete this->listaAviones[i];
	}
}
int ServidorXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion el VALOR debe estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO exite un setSizeBytes() este lo reemplaza
 */
void ServidorXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//cantidadMaximaClientes
		+ sizeof(int)//puerto
		+ sizeof(int)//canSprs
		+ sizeof(int);//canAvs
}
void ServidorXml::setId(int id){
	this->id = id;
}
int ServidorXml::getId(){
	return this->id;
}

void ServidorXml::setCantidadMaximaClientes(int cantidadMaximaClientes){
	this->cantidadMaximaClientes = cantidadMaximaClientes;
}
int ServidorXml::getCantidadMaximaClientes(){
	return this->cantidadMaximaClientes;
}
void ServidorXml::setPuerto(int puerto){
	this->puerto = puerto;
}
int ServidorXml::getPuerto(){
	return this->puerto;
}
void ServidorXml::setVentanaXml(const VentanaXml &ventanaXml){
	this->ventanaXml = ventanaXml;

}
VentanaXml * ServidorXml::getVentanaXmlCopy(){
	return &this->ventanaXml;
}
void ServidorXml::setEscenarioXml(const EscenarioXml &escenarioXml){
	this->escenarioXml = escenarioXml;
}
/*const */EscenarioXml * ServidorXml::getEscenarioXmlCopy(){
	return &this->escenarioXml;
}
void ServidorXml::addSprite(SpriteXml * sprite,int pos){
	this->canSprs++;
	this->listaSprite[pos] = sprite;
}
//listado de punteros
SpriteXml * * ServidorXml::getListaSprites(){
	return this->listaSprite;
}
int ServidorXml::getCanSprs(){
	return this->canSprs;
}

void ServidorXml::addAvion(AvionXml * avion,int pos){
	this->canAvs++;
	this->listaAviones[pos] = avion;
}
//listado de punteros a Aviones
AvionXml * * ServidorXml::getListaAviones(){
	return this->listaAviones;
}
int ServidorXml::getCanAvs(){
	return this->canAvs;
}

void ServidorXml::toString(TCadena1000 cadena){
	sprintf(cadena,"ServidorXml:sizeBytes=%d,id=%d,cantidadMaximaClientes=%d,puerto=%d,canSprs=%d,canAvs=%d",
		sizeBytes,id,cantidadMaximaClientes,puerto,canSprs,canAvs);
}
