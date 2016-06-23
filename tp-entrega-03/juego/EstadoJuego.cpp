#include "EstadoJuego.h"

EstadoJuego::EstadoJuego(EstadoAvion** estadoAvionJugador, int cantidadDeJugadores){
	for(int i = 0; i < cantidadDeJugadores; i++){
		estadoDeLosAviones.push_back(estadoAvionJugador[i]);
	}
	this->estadoMapa = new EstadoMapa();
	this->evento = new Evento(noHayNingunEventoEspecial);
}

EstadoJuego::EstadoJuego(Evento evento){
	this->estadoMapa = new EstadoMapa();
	this->evento = new Evento(evento.getNumeroDeEvento());
}

EstadoJuego::EstadoJuego(std::list<EstadoAvion*> estadoAvion, EstadoMapa* estadoDelMapa,
						std::list<EstadoJugador> estadoJugador){
	estadoDeLosAviones = estadoAvion;
	estadoMapa = estadoDelMapa;
	this->estadoJugador = estadoJugador;
	this->evento = new Evento(noHayNingunEventoEspecial);
} 

EstadoJuego::EstadoJuego(std::list<EstadoAvion*> estadoAvion, Evento evento,
							std::list<EstadoJugador> estadoJugador,EstadoMapa* estadoDelMapa){
	estadoDeLosAviones = estadoAvion;
	estadoMapa = estadoDelMapa;
	this->estadoJugador = estadoJugador;
	this->evento = new Evento(evento.getNumeroDeEvento());
} 

EstadoJuego::~EstadoJuego(){
	delete evento;
	std::list<EstadoAvion*> lista;
	std::list<EstadoAvion*>::iterator it;
	for (it = lista.begin(); it != lista.end(); it++) {
		delete (*it);
	}
	lista.clear();
}

std::list<EstadoAvion*> EstadoJuego::getEstadoDeLosAviones(){
	return estadoDeLosAviones;
}

EstadoMapa* EstadoJuego::getEstadoDelMapa() {
	return estadoMapa;
}

Evento* EstadoJuego::obtenerEvento(){
	return evento;
}

std::list<EstadoJugador> EstadoJuego::getEstadoDeLosJugadores(){
	return(this->estadoJugador);
}