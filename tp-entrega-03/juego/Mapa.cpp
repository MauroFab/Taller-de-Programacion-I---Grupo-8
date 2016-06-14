#include "Mapa.h"

Mapa::Mapa(ServidorXml* servidorXml){
	
	this->alto = servidorXml->getVentanaXmlCopy()->getAlto();
	this->tamanioMaximo = 2000;
	this->scrollingOffSet = 0;
	this->cantidadDePixelesQuePasaron = 0;
	this->estado = new EstadoMapa();
}

Mapa::~Mapa(){
	delete estado;
}

void Mapa::actualizar() {

	this->cantidadDePixelesQuePasaron++;
	this->scrollingOffSet++;

	if (this->cantidadDePixelesQuePasaron > this->tamanioMaximo) {
		this->estado->setCodigoReinicio(REINICIO);
		this->cantidadDePixelesQuePasaron = 0;
		this->scrollingOffSet = 0;
	}

	//Después de la ultima posicion de la imagen de fondo sigue la primera
	if(this->scrollingOffSet >= alto)
		this->scrollingOffSet = 0;

	this->estado->actualizar(this->cantidadDePixelesQuePasaron, this->scrollingOffSet);
}

EstadoMapa* Mapa::getEstado() {
	return this->estado;
}