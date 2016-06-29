#include "Mapa.h"

Mapa::Mapa(ServidorXml* servidorXml){
	
	this->altoVentana = servidorXml->getVentanaXmlCopy()->getAlto();
	this->tamanioMaximoMapa = MAX_ALTO_MAPA;
	this->cantidadDePixelesQuePasaron = 0;
	this->estado = new EstadoMapa();
	this->cantidadEtapas = servidorXml->getCanEsc();
	this->idEtapaActual = 0;
}

Mapa::~Mapa(){
	delete estado;
}

void Mapa::actualizar() {
	this->cantidadDePixelesQuePasaron++;
	this->estado->actualizar(this->cantidadDePixelesQuePasaron);
}

EstadoMapa* Mapa::getEstado() {
	return this->estado;
}

bool Mapa::seTerminoEtapa() {

	if (this->cantidadDePixelesQuePasaron > this->tamanioMaximoMapa) {
		this->estado->terminoEtapa();
		return true;
	} else {
		return false;
	}
}

void Mapa::avanzarEtapa() {
	this->cantidadDePixelesQuePasaron = 0;
	this->idEtapaActual++;
	this->estado->empezoEtapa();
	this->estado->setIdEtapa(this->idEtapaActual);
	this->estado->actualizar(this->cantidadDePixelesQuePasaron);
}

bool Mapa::seTerminoJuego() {
	return (this->idEtapaActual == (this->cantidadEtapas-1));
}

void Mapa::setJuegoFinalizado() {
	// El 2 es que se termino el juego
	this->estado->setCodigoReinicio(2);
}