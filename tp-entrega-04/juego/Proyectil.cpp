#include "Proyectil.h"

Proyectil::Proyectil(BalaView * balaView, bool mejorado) {
    velocidadX = 0;
    velocidadY = 0;
	frame = 0;

	altoFotograma = balaView->spriteXml->getAlto();
	anchoFotograma = balaView->spriteXml->getAncho();
	cantDeFotogramas = balaView->spriteXml->getCantidad();
	velocidad = balaView->balaModel->velBala;
	velocidadY += velocidad;
	this->mejorado = mejorado;
	huboUnImpacto = false;
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

void Proyectil::mover(std::list<AvionEnemigo*> &avionesEnemigos, ModeloJugador* jugadorQueDisparo,
					  std::list<PowerUp>& powerUps) {
	SuperficieOcupada hitbox;
	hitbox = superficie.desplazarEnYObteniendoHitbox(velocidadY);
	std::list<AvionEnemigo*>::iterator it;
	for(it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++){
		SuperficieOcupada superficieEnemigo;
		superficieEnemigo = (*it)->obtenerSuperficieOcupada();
		if(hitbox.meSolapoCon(superficieEnemigo) && !huboUnImpacto && !(*it)->estaDestruido()){
			(*it)->recibeUnImpacto(jugadorQueDisparo->getId());
			huboUnImpacto = true;
			jugadorQueDisparo->sumarPuntos((*it)->getPuntosQueOtorgaAlSerImpactado());
			if((*it)->estaDestruido()){
				jugadorQueDisparo->sumarPuntos((*it)->getPuntosQueOtorgaAlSerDestruido());
				if((*it)->dejaUnPowerUpAlSerDestruido())
					powerUps.push_back((*it)->getPowerUpQueDejaAlSerDestruido());
			}
		}
	}
}

EstadoProyectil* Proyectil::createEstado() {
	bool visible = !huboUnImpacto;
	return new EstadoProyectil(frame, superficie.obtenerPosicion().getPosX() , 
										superficie.obtenerPosicion().getPosY() , mejorado,
										visible);
}

bool Proyectil::getHuboUnImpacto() {
	return huboUnImpacto;
}