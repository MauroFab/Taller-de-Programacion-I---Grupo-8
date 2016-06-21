#include "Proyectil.h"

Proyectil::Proyectil(BalaView * balaView) {
    velocidadX = 0;
    velocidadY = 0;
	frame = 0;

	altoFotograma = balaView->spriteXml->getAlto();
	anchoFotograma = balaView->spriteXml->getAncho();
	cantDeFotogramas = balaView->spriteXml->getCantidad();
	velocidad = balaView->balaModel->velBala;
	velocidadY -= velocidad;
}

Proyectil::~Proyectil(void) {
}

void Proyectil::setCoordenasDeComienzo(int posX, int posY) {
	posicionX = posX;
	posicionY = posY;
}

bool Proyectil::estaEnPantalla() {
	return (posicionY >= - FAKE_2_SCREEN_HEIGHT);
}

void Proyectil::mover() {
	posicionY += velocidadY;
}

EstadoProyectil* Proyectil::createEstado() {
	return new EstadoProyectil(frame, posicionX, posicionY);
}