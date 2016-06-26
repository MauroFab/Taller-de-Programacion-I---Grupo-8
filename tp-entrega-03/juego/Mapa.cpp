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
	if (this->cantidadDePixelesQuePasaron > this->tamanioMaximoMapa) {
		this->cantidadDePixelesQuePasaron = 0;
		this->idEtapaActual++;
		this->estado->setIdEtapa(this->idEtapaActual);
	}
	this->estado->actualizar(this->cantidadDePixelesQuePasaron);
}

EstadoMapa* Mapa::getEstado() {
	return this->estado;
}