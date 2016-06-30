#include "Mapa.h"

Mapa::Mapa(ServidorXml* servidorXml){
	
	this->altoVentana = servidorXml->getVentanaXmlCopy()->getAlto();
	this->tamanioMaximoMapa = MAX_ALTO_MAPA;
	this->cantidadDePixelesQuePasaron = 0;
	this->estado = new EstadoMapa();
	this->cantidadEtapas = servidorXml->getCanEsc();
	this->idEtapaActual = 0;
	this->finalizacionAbrupta = false;
	this->noHayMasAviones = false;
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
	return (this->idEtapaActual == (this->cantidadEtapas-1) || this->finalizacionAbrupta || this->noHayMasAviones);
}

void Mapa::setJuegoFinalizado() {
	// El 2 es que se termino el juego
	this->estado->setCodigoReinicio(2);
}

void Mapa::finalizarJuegoPorEvento() {
	this->finalizacionAbrupta = true;
}

void Mapa::finalizarJuegoPorQueNoHayAviones() {
	this->noHayMasAviones = true;
}

bool Mapa::seEstaLLegandoAlFinalDeLaEtapa() {
	return (this->cantidadDePixelesQuePasaron + 200 > 2000);
}

bool Mapa::empezoUnaNuevaEtapa() {
	return (this->cantidadDePixelesQuePasaron == 0);
}

void Mapa::reiniciar() {
	this->cantidadDePixelesQuePasaron = 0;
	this->idEtapaActual = 0;
	this->finalizacionAbrupta = false;
	this->noHayMasAviones = false;
}