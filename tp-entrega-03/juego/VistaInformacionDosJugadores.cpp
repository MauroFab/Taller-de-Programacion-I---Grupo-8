#include "VistaInformacionDosJugadores.h"

VistaInformacionDosJugadores::VistaInformacionDosJugadores(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionColaboracionDosJugador.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1 = new Etiqueta(this->renderer, this->font);
	this->usuario1->setPosicion(100, 170);
	this->usuario2 = new Etiqueta(this->renderer, this->font);
	this->usuario2->setPosicion(100, 230);
	this->puntos1 = new Etiqueta(this->renderer, this->font);
	this->puntos1->setPosicion(310, 170);
	this->puntos2 = new Etiqueta(this->renderer, this->font);
	this->puntos2->setPosicion(310, 230);
	this->usuarioGanadaor = new Etiqueta(this->renderer, this->font);
	this->usuarioGanadaor->setPosicion(100, 370);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(310, 370);
}

VistaInformacionDosJugadores::~VistaInformacionDosJugadores(void) {
	delete this->fondo;
	delete this->usuario1;
	delete this->usuario2;
	delete this->puntos1;
	delete this->puntos2;
	delete this->usuarioGanadaor;
	delete this->puntosGanador;
}

void VistaInformacionDosJugadores::mostrar(std::list<EstadoJugador> estadosJugadores) {
}