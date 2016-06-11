#include "EstadoJuego.h"


EstadoJuego::EstadoJuego(EstadoAvion** estadoAvionJugador, int cantidadDeJugadores){
	for(int i = 0; i < cantidadDeJugadores; i++){
		estadoDeLosAviones.push_back(estadoAvionJugador[i]);
	}
}

EstadoJuego::EstadoJuego(std::list<EstadoAvion*> estadoAvion){
	estadoDeLosAviones = estadoAvion;
} 



EstadoJuego::~EstadoJuego(){
	
}

std::list<EstadoAvion*> EstadoJuego::getEstadoDeLosAviones(){
	return estadoDeLosAviones;
}