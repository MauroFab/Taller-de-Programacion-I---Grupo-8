#include "VistaInformacionEquipos.h"

VistaInformacionEquipos::VistaInformacionEquipos(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionEquipos.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1E1 = new Etiqueta(this->renderer, this->font);
	this->usuario1E1->setPosicion(80, 180);
	this->usuario2E1 = new Etiqueta(this->renderer, this->font);
	this->usuario2E1->setPosicion(80, 240);
	this->usuario3E1 = new Etiqueta(this->renderer, this->font);
	this->usuario3E1->setPosicion(80, 300);
	this->usuario1E2 = new Etiqueta(this->renderer, this->font);
	this->usuario1E2->setPosicion(260, 180);
	this->usuario2E2 = new Etiqueta(this->renderer, this->font);
	this->usuario2E2->setPosicion(260, 240);
	this->usuario3E2 = new Etiqueta(this->renderer, this->font);
	this->usuario3E2->setPosicion(260, 300);
	this->puntos1E1 = new Etiqueta(this->renderer, this->font);
	this->puntos1E1->setPosicion(190, 180);
	this->puntos2E1 = new Etiqueta(this->renderer, this->font);
	this->puntos2E1->setPosicion(190, 240);
	this->puntos3E1 = new Etiqueta(this->renderer, this->font);
	this->puntos3E1->setPosicion(190, 300);
	this->puntos1E2 = new Etiqueta(this->renderer, this->font);
	this->puntos1E2->setPosicion(370, 180);
	this->puntos2E2 = new Etiqueta(this->renderer, this->font);
	this->puntos2E2->setPosicion(370, 240);
	this->puntos3E2 = new Etiqueta(this->renderer, this->font);
	this->puntos3E2->setPosicion(370, 300);
	this->equipoGanadaor = new Etiqueta(this->renderer, this->font);
	this->equipoGanadaor->setPosicion(140, 450);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(300, 450);
}

VistaInformacionEquipos::~VistaInformacionEquipos(void) {
	delete this->fondo;
	delete this->usuario1E1;
	delete this->usuario2E1;
	delete this->usuario3E1;
	delete this->usuario1E2;
	delete this->usuario2E2;
	delete this->usuario3E2;
	delete this->puntos1E1;
	delete this->puntos2E1;
	delete this->puntos3E1;
	delete this->puntos1E2;
	delete this->puntos2E2;
	delete this->puntos3E2;
	delete this->equipoGanadaor;
	delete this->puntosGanador;
}

void VistaInformacionEquipos::mostrar(std::list<EstadoJugador> estadosJugadores) {
}