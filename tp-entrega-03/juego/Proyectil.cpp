#include "Proyectil.h"

Proyectil::Proyectil(BalaView * balaView, bool mejorado) {
    velocidadX = 0;
    velocidadY = 0;
	frame = 0;

	altoFotograma = balaView->spriteXml->getAlto();
	anchoFotograma = balaView->spriteXml->getAncho();
	cantDeFotogramas = balaView->spriteXml->getCantidad();
	velocidad = balaView->balaModel->velBala;
	velocidadY -= velocidad;
	this->mejorado = mejorado;
	
}

Proyectil::~Proyectil(void) {
}

void Proyectil::setCoordenasDeComienzo(int posX, int posY) {
	if(mejorado){
		this->superficie = SuperficieOcupada(posX,posY,anchoFotograma,altoFotograma);
	}else{
		this->superficie = SuperficieOcupada(posX,posY,
								ANCHO_PROYECTIL_SIN_MEJORA, ALTO_PROYECTIL_SIN_MEJORA);
	}
}

bool Proyectil::estaEnPantalla() {
	return (superficie.obtenerPosicion().getPosY() >= - FAKE_2_SCREEN_HEIGHT);
}

void Proyectil::mover() {
	superficie.desplazarEnYObteniendoHitbox(velocidadY);
}

EstadoProyectil* Proyectil::createEstado() {
	return new EstadoProyectil(frame, superficie.obtenerPosicion().getPosX() , 
										superficie.obtenerPosicion().getPosY() , mejorado);
}