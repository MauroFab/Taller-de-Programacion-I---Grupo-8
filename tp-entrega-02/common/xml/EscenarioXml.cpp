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
}

EscenarioXml::~EscenarioXml()
{
	for (int i = 0; i < MAX_ELEMENTOS; i++){
		if (this->lista[i] != NULL)
			delete this->lista[i];
	}
}
EscenarioXml & EscenarioXml::operator = (const EscenarioXml & source)
{
	this->ancho = source.ancho;
	this->alto = source.alto;
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
		+ sizeof(int);//canElems
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

void EscenarioXml::toString(TCadena1000 cadena){
	sprintf(cadena,"EscenarioXml:ancho=%d,alto=%d,canElems=%d",ancho,alto,canElems);
}
