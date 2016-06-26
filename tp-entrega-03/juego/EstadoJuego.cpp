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

EstadoJuego::EstadoJuego(std::list<EstadoAvion*> estadoAvion, std::list<EstadoJugador> estadoJugador,
						std::list<EstadoPowerUp> estadoPowerUp, EstadoMapa* estadoDelMapa){
	estadoDeLosAviones = estadoAvion;
	estadoMapa = estadoDelMapa;
	this->estadoJugador = estadoJugador;
	this->evento = new Evento(noHayNingunEventoEspecial);
	this->estadoPowerUps = estadoPowerUp;
} 

EstadoJuego::EstadoJuego(std::list<EstadoAvion*> estadoAvion, std::list<EstadoJugador> estadoJugador,
						std::list<EstadoPowerUp> estadoPowerUp,
						EstadoMapa* estadoDelMapa, Evento evento){
	estadoDeLosAviones = estadoAvion;
	estadoMapa = estadoDelMapa;
	this->estadoJugador = estadoJugador;
	this->evento = new Evento(evento.getNumeroDeEvento());
	this->estadoPowerUps = estadoPowerUp;
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

std::list<EstadoPowerUp> EstadoJuego::getEstadoPowerUps(){
	return(this->estadoPowerUps);
}
void EstadoJuego::toString(TCadena1000 cadena){
	int cantidadDeAviones = getEstadoDeLosAviones().size();
	int cantidadDeJugadores = getEstadoDeLosJugadores().size();
	sprintf(cadena,"\nEstadoJuego: cantidadDeAvioness=%d,cantidadDeJugadores=%d,",cantidadDeAviones,cantidadDeJugadores);
}