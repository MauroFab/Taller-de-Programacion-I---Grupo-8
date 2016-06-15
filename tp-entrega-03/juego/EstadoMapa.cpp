#include "EstadoMapa.h"

EstadoMapa::EstadoMapa() {
	this->scrollingOffSet = 0;
	this->cantidadDePixelesQuePasaron = 0;
	this->codigoReinicio = 0;
}

EstadoMapa::~EstadoMapa(void) {
}

void EstadoMapa::actualizar(int cantidadPixeles, int offSet) {
	this->cantidadDePixelesQuePasaron = cantidadPixeles;
	this->scrollingOffSet = offSet;
}

int EstadoMapa::getScrollingOffSet() {
	return this->scrollingOffSet;
}

int EstadoMapa::getCantidadDePixeles() {
	return this->cantidadDePixelesQuePasaron;
}

int EstadoMapa::getCodigoReinicio() {
	return this->codigoReinicio;
}

int EstadoMapa::getSizeBytes() {
	return sizeof(int)/*scrollingOffSet*/ + sizeof(int)/*cantidadDePixelesQuePasaron*/+ sizeof(int)/*codigoDeReinicio*/;
}

void EstadoMapa::setScrollingOffSet(int offSet) {
	this->scrollingOffSet = offSet;
}

void EstadoMapa::setCantidaDePixeles(int pixeles) {
	this->cantidadDePixelesQuePasaron = pixeles;
}

void EstadoMapa::setCodigoReinicio(int codigo) {
	this->codigoReinicio = codigo;
}