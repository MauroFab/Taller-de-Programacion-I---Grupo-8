#include "Mapa.h"

Mapa::Mapa(ServidorXml* servidorXml){
	
	this->altoVentana = servidorXml->getVentanaXmlCopy()->getAlto();
	this->tamanioMaximoMapa = MAX_ALTO_MAPA;
	this->cantidadDePixelesQuePasaron = 0;
	this->estado = new EstadoMapa();
}

Mapa::~Mapa(){
	delete estado;
}

void Mapa::actualizar() {
	this->cantidadDePixelesQuePasaron++;
	if (this->cantidadDePixelesQuePasaron > this->tamanioMaximoMapa) {
		this->estado->setCodigoReinicio(REINICIO);
		this->cantidadDePixelesQuePasaron = 0;
	} else {
		this->estado->setCodigoReinicio(NO_REINICIO);
	}

	this->estado->actualizar(this->cantidadDePixelesQuePasaron);
}

EstadoMapa* Mapa::getEstado() {
	return this->estado;
}