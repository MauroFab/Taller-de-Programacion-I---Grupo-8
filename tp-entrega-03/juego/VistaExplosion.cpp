#include "VistaExplosion.h"
#include "CacheSonido.h"

VistaExplosion::VistaExplosion(SDL_Renderer* renderer){
	//Pongo todas las posiciones relevantes del mapa en false
	for(int i = 0; i < 10; i++){
		this->yaPaseElSonidoDelJugador[i] = false;
	}
	for(int i = 0; i < 10; i++){
		this->iteracionesDesdeQueExplotoElAvion[i] = 0;
	}
	renderer = renderer;
	char path[200]= "../cliente1942/explosionBasica.bmp";
	this->texturaExplosion = new Textura();
	texturaExplosion->cargarDeArchivo(path,renderer);
	this->renderer = renderer;
}


VistaExplosion::~VistaExplosion(void){

}


void VistaExplosion::graficarExplosion(EstadoAvion* estadoAvion){
	SDL_Rect fotograma;
	fotograma.x = 0;
	fotograma.y = 0;
	fotograma.w = texturaExplosion->getWidth();
	fotograma.h = texturaExplosion->getHeight();
	//600 es mas o menos la altura del mapa (640) menos la altura de un avion de un jugador
	texturaExplosion->render(estadoAvion->getPosX(),600 - estadoAvion->getPosY(),renderer,&fotograma);
}
void VistaExplosion::procesarEstadoAvionQueEstaDestruido(EstadoAvion* estadoAvion){
	if(esUnAvionDeUnJugador(estadoAvion)){
		if(!yaPaseElSonidoDeExplosionDe(estadoAvion)){
			Mix_PlayChannel( -1, CacheSonido::getInstance()->getChunk(EXPLOSION), 0 );
			yaPaseElSonidoDelJugador[estadoAvion->getId()] = true;
		}
		if(iteracionesDesdeQueExplotoElAvion[estadoAvion->getId()] < 100){
			graficarExplosion(estadoAvion);
			iteracionesDesdeQueExplotoElAvion[estadoAvion->getId()]++;
		}
	}
}

bool VistaExplosion::yaPaseElSonidoDeExplosionDe(EstadoAvion* estadoAvion){
	return yaPaseElSonidoDelJugador[estadoAvion->getId()];
}

bool VistaExplosion::esUnAvionDeUnJugador(EstadoAvion* estadoAvion){
	//Las ids de los enemigos son mayores o iguales a 100, las chiquitas son de aviones jugadores
	return(estadoAvion->getId() < 10);
}
