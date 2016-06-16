#include "EstadoMapa.h"

EstadoMapa::EstadoMapa() {
	this->cantidadDePixelesQuePasaron = 0;
	this->codigoReinicio = 0;
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

void EstadoMapa::setCantidaDePixeles(int pixeles) {
	this->cantidadDePixelesQuePasaron = pixeles;
}

void EstadoMapa::setCodigoReinicio(int codigo) {
	this->codigoReinicio = codigo;
}

int EstadoMapa::getSizeBytes() {
	return sizeof(int)/*cantidadDePixelesQuePasaron*/+ sizeof(int)/*codigoDeReinicio*/;
}
