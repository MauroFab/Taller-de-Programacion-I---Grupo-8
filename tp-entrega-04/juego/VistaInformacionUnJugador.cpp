#include "VistaInformacionUnJugador.h"

VistaInformacionUnJugador::VistaInformacionUnJugador(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionColaboracionUnJugador.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->nombreUsuario = new Etiqueta(this->renderer, this->font);
	this->nombreUsuario->setPosicion(130, 170);
	this->puntos = new Etiqueta(this->renderer, this->font);
	this->puntos->setPosicion(310, 170);
}

VistaInformacionUnJugador::~VistaInformacionUnJugador(void) {
	delete this->fondo;
	delete this->nombreUsuario;
	delete this->puntos;
}

void VistaInformacionUnJugador::mostrar(std::list<EstadoJugador> estadosJugadores) {

	EstadoJugador estado = estadosJugadores.front();

	string nombre = estado.getNombreUsuario();
	string puntos = StringUtil::intToString(estado.getPuntajeAcumulado());

	this->nombreUsuario->setTexto(nombre);
	this->puntos->setTexto(puntos);

	this->fondo->render();
	this->nombreUsuario->render();
	this->puntos->render();
}