#include "ConfiguracionProyectilXML.h"


ConfiguracionProyectilXML::ConfiguracionProyectilXML(std::string path, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma, int velocidad) {

	this->pathImagen = path;
	this->cantidadDeFotogramas = cantidadDeFotogramas;
	this->anchoFotograma = anchoFotograma;
	this->altoFotograma = altoFotograma;
	this->velocidad = velocidad;
}

ConfiguracionProyectilXML::~ConfiguracionProyectilXML(void) {
}

std::string ConfiguracionProyectilXML::getPathImagen() {
	return pathImagen;
}

int ConfiguracionProyectilXML::getCantidadDeFotogramas() {
	return cantidadDeFotogramas;
}

int ConfiguracionProyectilXML::getAnchoFotograma() {
	return anchoFotograma;
}

int ConfiguracionProyectilXML::getAltoFotograma() {
	return altoFotograma;
}

int ConfiguracionProyectilXML::getVelocidad() {
	return velocidad;
}