#include "ServidorXml.h"
/* @autor sabris
 */
ServidorXml::ServidorXml()
{
	this->sizeBytes = -1;
	this->cantidadMaximaClientes = -1;
	this->puerto = -1;
	this->modo = -1;
//	VentanaXml ventanaXml;
	for (int i = 0; i < MAX_ESCENARIOS; i++){
		this->listaEscenario[i] = NULL;
	}
	this->canEsc = 0;
	for (int i = 0; i < MAX_SPRITES; i++){
		this->listaSprite[i] = NULL;
	}
	this->canSprs = 0;
	for (int i = 0; i < MAX_AVIONES; i++){
		this->listaAviones[i] = NULL;
	}
	this->canAvs = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++){
		this->listaEnemigos[i] = NULL;
	}
	this->canEnes = 0;
	for (int i = 0; i < MAX_POWERUPS; i++){
		this->listaPowerUp[i] = NULL;
	}
	this->canPows = 0;
}

ServidorXml::~ServidorXml()
{
	for (int i = 0; i < MAX_ESCENARIOS; i++){
		if (this->listaEscenario[i] != NULL)
			delete this->listaEscenario[i];
	}
	for (int i = 0; i < MAX_SPRITES; i++){
		if (this->listaSprite[i] != NULL)
			delete this->listaSprite[i];
	}
	for (int i = 0; i < MAX_AVIONES; i++){
		if (this->listaAviones[i] != NULL)
			delete this->listaAviones[i];
	}
	for (int i = 0; i < MAX_ENEMIGOS; i++){
		if (this->listaEnemigos[i] != NULL)
			delete this->listaEnemigos[i];
	}
	for (int i = 0; i < MAX_POWERUPS; i++){
		if (this->listaPowerUp[i] != NULL)
			delete this->listaPowerUp[i];
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
		+ sizeof(int)//cantidadMaximaClientes
		+ sizeof(int)//puerto
		+ sizeof(int)//canEsc
		+ sizeof(int)//canSprs
		+ sizeof(int)//canAvs
		+ sizeof(int)//canEnes
		+ sizeof(int);//canPows
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

void ServidorXml::setModo(int modo){
	this->modo = modo;
}
int ServidorXml::getModo(){
	return this->modo;
}

void ServidorXml::setVentanaXml(const VentanaXml &ventanaXml){
	this->ventanaXml = ventanaXml;

}
VentanaXml * ServidorXml::getVentanaXmlCopy(){
	return &this->ventanaXml;
}

void ServidorXml::addEscenario(EscenarioXml * escenario,int pos){
	this->canEsc++;
	this->listaEscenario[pos] = escenario;
}
//listado de punteros a EscenarioXml
EscenarioXml * * ServidorXml::getListaEscenario(){
	return this->listaEscenario;
}
int ServidorXml::getCanEsc(){
	return this->canEsc;
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
void ServidorXml::addEnemigo(AvionEnemigoXml * enemigo,int pos){
	this->canEnes++;
	this->listaEnemigos[pos] = enemigo;
}
//listado de punteros a Enemigos
AvionEnemigoXml * * ServidorXml::getListaEnemigos(){
	return this->listaEnemigos;
}
int ServidorXml::getCanEnes(){
	return this->canEnes;
}
void ServidorXml::addPowerUp(PowerUpXml * powU,int pos){
	this->canPows++;
	this->listaPowerUp[pos] = powU;
}
//listado de punteros a PowerUpXml
PowerUpXml * * ServidorXml::getListaPowerUp(){
	return this->listaPowerUp;
}
int ServidorXml::getCanPows(){
	return this->canPows;
}

void ServidorXml::toString(TCadena1000 cadena){
	sprintf(cadena,"ServidorXml:sizeBytes=%dcantidadMaximaClientes=%d,puerto=%d,canEsc=%d,canSprs=%d,canAvs=%d",
		sizeBytes,cantidadMaximaClientes,puerto,canEsc,canSprs,canAvs);
}
