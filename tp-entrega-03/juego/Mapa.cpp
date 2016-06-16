#include "Mapa.h"

Mapa::Mapa(ServidorXml* servidorXml){
	
	this->alto = servidorXml->getVentanaXmlCopy()->getAlto();
	this->tamanioMaximo = 2000;
	this->cantidadDePixelesQuePasaron = 0;
	this->estado = new EstadoMapa();
}

Mapa::~Mapa(){
	delete estado;
}

void Mapa::actualizar() {

	this->cantidadDePixelesQuePasaron++;

	if (this->cantidadDePixelesQuePasaron > this->tamanioMaximo) {
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