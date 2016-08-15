#include "AvionSecundario.h"

AvionSecundario::AvionSecundario() {
	this->visible = false;
	this->superficieOcupada = new SuperficieOcupada(0,0, ANCHO, ALTO);
}

AvionSecundario::~AvionSecundario() {
	delete superficieOcupada;
}

bool AvionSecundario::esVisible() {
	return this->visible;
}

void AvionSecundario::hacerVisible() {
	this->visible = true;
}

void AvionSecundario::setPosicion(int x, int y) {

	this->superficieOcupada->moverAPosicion(Posicion(x, y));
}

int AvionSecundario::getAncho() {

	return ANCHO;
}

int AvionSecundario::getAlto() {

	return ALTO;
}