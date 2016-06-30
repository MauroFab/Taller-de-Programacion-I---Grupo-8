#include "EscenarioXml.h"
/* @autor sabris
 */
EscenarioXml::EscenarioXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->ancho = -1;
	this->alto = -1;
	for (int i = 0; i < MAX_ELEMENTOS; i++){
		this->lista[i] = NULL;
	}
	this->canElems = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++){
		this->listaEnemigos[i] = NULL;
	}
	this->canEnes = 0;
	for (int i = 0; i < MAX_POWERUPS; i++){
		this->listaPowerUp[i] = NULL;
	}
	this->canPows = 0;
}
EscenarioXml::EscenarioXml(int id)
{
	this->sizeBytes = -1;
	this->id = id;
	this->ancho = -1;
	this->alto = -1;
	for (int i = 0; i < MAX_ELEMENTOS; i++){
		this->lista[i] = NULL;
	}
	this->canElems = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++){
		this->listaEnemigos[i] = NULL;
	}
	this->canEnes = 0;
	for (int i = 0; i < MAX_POWERUPS; i++){
		this->listaPowerUp[i] = NULL;
	}
	this->canPows = 0;
}

EscenarioXml::~EscenarioXml()
{
	for (int i = 0; i < MAX_ELEMENTOS; i++){
		if (this->lista[i] != NULL)
			delete this->lista[i];
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
EscenarioXml & EscenarioXml::operator = (const EscenarioXml & source)
{
	this->ancho = source.ancho;
	this->alto = source.alto;
	this->fondoXml = source.fondoXml;
	this->canElems = source.canElems;
	for (int i = 0; i < canElems; i++){
		this->lista[i] = new ElementoXml();
		(*this->lista[i]) = (*source.lista[i]);
	}

    return *this;
};
int EscenarioXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion los VALORES char* deben estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO existe un setSizeBytes() este lo reemplaza
 */
void EscenarioXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//ancho
		+ sizeof(int)//alto
		+ sizeof(int)//canElems
		+ sizeof(int)//canEnem
		+ sizeof(int);//canPows
}
void EscenarioXml::setId(int id){
	this->id = id;
}
int EscenarioXml::getId(){
	return this->id;
}

void EscenarioXml::setAncho(int ancho){
	this->ancho = ancho;
}
int EscenarioXml::getAncho(){
	return this->ancho;
}
void EscenarioXml::setAlto(int alto){
	this->alto = alto;
}
int EscenarioXml::getAlto(){
	return this->alto;
}

void EscenarioXml::setFondoXml(const FondoXml &fondoXml){
	this->fondoXml = fondoXml;
}
/*const */FondoXml * EscenarioXml::getFondoXmlCopy(){
	return &this->fondoXml;
}
void EscenarioXml::addElemento(ElementoXml * elemento,int pos){
	this->canElems++;
	this->lista[pos] = elemento;
}
//listado de punteros
ElementoXml * * EscenarioXml::getListaElementos(){
	return this->lista;
}
int EscenarioXml::getCanElems(){
	return this->canElems;
}

void EscenarioXml::addEnemigo(AvionEnemigoXml * enemigo,int pos){
	this->canEnes++;
	this->listaEnemigos[pos] = enemigo;
}
//listado de punteros a Enemigos
AvionEnemigoXml * * EscenarioXml::getListaEnemigos(){
	return this->listaEnemigos;
}
int EscenarioXml::getCanEnes(){
	return this->canEnes;
}
void EscenarioXml::addPowerUp(PowerUpXml * powU,int pos){
	this->canPows++;
	this->listaPowerUp[pos] = powU;
}
//listado de punteros a PowerUpXml
PowerUpXml * * EscenarioXml::getListaPowerUp(){
	return this->listaPowerUp;
}
int EscenarioXml::getCanPows(){
	return this->canPows;
}

void EscenarioXml::toString(TCadena1000 cadena){
	sprintf(cadena,"EscenarioXml:ancho=%d,alto=%d,canElems=%d,canEnemigos=%d,canPowUp=%d",ancho,alto,canElems,canEnes,canPows);
}
