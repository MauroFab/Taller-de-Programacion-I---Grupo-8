#include "VistaInformacionTresJugadores.h"

VistaInformacionTresJugadores::VistaInformacionTresJugadores(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionColaboracionTresJugadores.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1 = new Etiqueta(this->renderer, this->font);
	this->usuario1->setPosicion(100, 170);
	this->usuario2 = new Etiqueta(this->renderer, this->font);
	this->usuario2->setPosicion(100, 230);
	this->usuario3 = new Etiqueta(this->renderer, this->font);
	this->usuario3->setPosicion(100, 300);
	this->puntos1 = new Etiqueta(this->renderer, this->font);
	this->puntos1->setPosicion(310, 170);
	this->puntos2 = new Etiqueta(this->renderer, this->font);
	this->puntos2->setPosicion(310, 230);
	this->puntos3 = new Etiqueta(this->renderer, this->font);
	this->puntos3->setPosicion(310, 300);
	this->usuarioGanadaor = new Etiqueta(this->renderer, this->font);
	this->usuarioGanadaor->setPosicion(100, 455);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(310, 455);
}

VistaInformacionTresJugadores::~VistaInformacionTresJugadores(void) {
	delete this->fondo;
	delete this->usuario1;
	delete this->usuario2;
	delete this->usuario3;
	delete this->puntos1;
	delete this->puntos2;
	delete this->puntos3;
	delete this->usuarioGanadaor;
	delete this->puntosGanador;
}

void VistaInformacionTresJugadores::mostrar(std::list<EstadoJugador> estadosJugadores) {
}