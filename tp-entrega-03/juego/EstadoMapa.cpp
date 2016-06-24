#include "EstadoMapa.h"

EstadoMapa::EstadoMapa() {
	this->cantidadDePixelesQuePasaron = 0;
	this->codigoReinicio = 0;
	this->idEtapa = 0;
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

void EstadoMapa::setCantidaDePixeles(int pixeles) {
	this->cantidadDePixelesQuePasaron = pixeles;
}

void EstadoMapa::setCodigoReinicio(int codigo) {
	this->codigoReinicio = codigo;
}

void EstadoMapa::setIdEtapa(int id) {
	this->idEtapa = id;
}

int EstadoMapa::getSizeBytes() {
	return sizeof(int)/*cantidadDePixelesQuePasaron*/
	 +sizeof(int)/*codigoDeReinicio*/
	 + sizeof(int)/*idEtapa*/;
}
