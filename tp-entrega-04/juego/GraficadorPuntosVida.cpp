#include "GraficadorPuntosVida.h"

GraficadorPuntosVida::GraficadorPuntosVida(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->etiqueta = new Etiqueta(this->renderer,TTF_OpenFont("sfd/FreeSans.ttf", 24));
	this->etiqueta->setPosicion(0,600);
	this->puntosDeVida = 3;

	string puntos = convertirPuntajeAString();
	this->etiqueta->setTexto(puntos);
}

GraficadorPuntosVida::~GraficadorPuntosVida(void) {
	delete this->etiqueta;
}

void GraficadorPuntosVida::renderizarPuntosDeVida(int puntos) {

	if (puntos != this->puntosDeVida) {
		
		this->puntosDeVida = puntos;

		string puntaje = this->convertirPuntajeAString();
		this->etiqueta->setTexto(puntaje);
	}

	this->etiqueta->render();
}

string GraficadorPuntosVida::convertirPuntajeAString() {

	string puntos = static_cast<ostringstream*>( &(ostringstream() << this->puntosDeVida) )->str();
	string puntaje("Vidas: ");
	puntaje.append(puntos);

	return puntaje;
}