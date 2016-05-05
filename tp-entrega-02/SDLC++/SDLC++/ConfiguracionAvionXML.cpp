#include "ConfiguracionAvionXML.h"


ConfiguracionAvionXML::ConfiguracionAvionXML(std::string path, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma, int velocidad) {

	this->pathImagen = path;
	this->cantidadDeFotogramas = cantidadDeFotogramas;
	this->anchoFotograma = anchoFotograma;
	this->altoFotograma = altoFotograma;
	this->velocidad = velocidad;
}

ConfiguracionAvionXML::~ConfiguracionAvionXML(void) {
}

std::string ConfiguracionAvionXML::getPathImagen() {
	return pathImagen;
}

int ConfiguracionAvionXML::getCantidadDeFotogramas() {
	return cantidadDeFotogramas;
}

int ConfiguracionAvionXML::getAnchoFotograma() {
	return anchoFotograma;
}

int ConfiguracionAvionXML::getAltoFotograma() {
	return altoFotograma;
}

int ConfiguracionAvionXML::getVelocidad() {
	return velocidad;
}