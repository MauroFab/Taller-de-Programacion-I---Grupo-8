#include "EstadoMapa.h"

EstadoMapa::EstadoMapa() {
	this->sizeBytes = -1;
	this->cantidadDePixelesQuePasaron = 0;
	this->codigoReinicio = 0;
	this->idEtapa = 0;
	this->mostrarInformacion = false;
}

EstadoMapa::~EstadoMapa(void) {
}

void EstadoMapa::actualizar(int cantidadPixeles) {
	this->cantidadDePixelesQuePasaron = cantidadPixeles;
}

int EstadoMapa::getCantidadDePixeles() {
	return this->cantidadDePixelesQuePasaron;
}

int EstadoMapa::getCodigoReinicio() {
	return this->codigoReinicio;
}

int EstadoMapa::getIdEtapa() {
	return this->idEtapa;
}

bool EstadoMapa::hayQueMostrarInformacion() {
	return this->mostrarInformacion;
}

void EstadoMapa::setCantidaDePixeles(int pixeles) {
	this->cantidadDePixelesQuePasaron = pixeles;
}

void EstadoMapa::setCodigoReinicio(int codigo) {
	this->codigoReinicio = codigo;
}

void EstadoMapa::setIdEtapa(int id) {
	this->idEtapa = id;
}

void EstadoMapa::terminoEtapa() {
	this->mostrarInformacion = true;
}

void EstadoMapa::empezoEtapa() {
	this->mostrarInformacion = false;
}

int EstadoMapa::getSizeBytes() {
	return sizeof(int)/*cantidadDePixelesQuePasaron*/
	+ sizeof(int)/*codigoDeReinicio*/
	+ sizeof(int)/*idEtapa*/
	+ sizeof(bool)/*mostrarInformacion*/;
}
void EstadoMapa::calculateSizeBytes(){
	this->sizeBytes = sizeof(int)/*cantidadDePixelesQuePasaron*/
	+ sizeof(int)/*codigoDeReinicio*/
	+ sizeof(int)/*idEtapa*/
	+ sizeof(bool)/*mostrarInformacion*/;	
}
void EstadoMapa::toString(TCadena1000 cadena){
	sprintf(cadena,"\nEstadoMapa: sizeBytes=%d,cantidadDePixelesQuePasaron=%d,codigoReinicio=%d,idEtapa=%d",
	sizeBytes,cantidadDePixelesQuePasaron,codigoReinicio,idEtapa);
}