#include "VistaExplosion.h"
#include "CacheSonido.h"

VistaExplosion::VistaExplosion(void){
	//Pongo todas las posiciones relevantes del mapa en false
	for(int i = 0; i < 1000; i++){
		this->yaPaseElSonidoDelJugador[i] = false;
	}
}


VistaExplosion::~VistaExplosion(void){

}

void VistaExplosion::procesarEstadoAvionQueEstaDestruido(EstadoAvion* estadoAvion){
	if(esUnAvionDeUnJugador(estadoAvion) && !yaPaseElSonidoDeExplosionDe(estadoAvion)){
		Mix_PlayChannel( -1, CacheSonido::getInstance()->getChunk(EXPLOSION), 0 );
		yaPaseElSonidoDelJugador[estadoAvion->getId()] = true;
	}
}

bool VistaExplosion::yaPaseElSonidoDeExplosionDe(EstadoAvion* estadoAvion){
	return yaPaseElSonidoDelJugador[estadoAvion->getId()];
}

bool VistaExplosion::esUnAvionDeUnJugador(EstadoAvion* estadoAvion){
	//Las ids de los enemigos son mayores o iguales a 100, las chiquitas son de aviones jugadores
	return(estadoAvion->getId() < 10);
}
