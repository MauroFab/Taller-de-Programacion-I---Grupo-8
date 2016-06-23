#include "GraficadorPuntaje.h"

GraficadorPuntaje::GraficadorPuntaje(SDL_Renderer* renderer){
	this->renderer = renderer;
	SDL_Color White = {255, 255, 255, 0};
	this->etiqueta = new Etiqueta(this->renderer, TTF_OpenFont("sfd/FreeSans.ttf", 24), White);
	this->etiqueta->setPosicion(0,0);
	this->puntaje = 0;

	string puntaje = this->convertirPuntajeAString();
	this->etiqueta->setTexto(puntaje);
}

void GraficadorPuntaje::renderizarPuntaje(int puntaje){

	if (puntaje != this->puntaje) {
		
		this->puntaje = puntaje;

		string puntaje = this->convertirPuntajeAString();
		this->etiqueta->setTexto(puntaje);
	}

	this->etiqueta->render();
}

GraficadorPuntaje::~GraficadorPuntaje(void) {
	delete this->etiqueta;
}

string GraficadorPuntaje::convertirPuntajeAString() {

	string puntos = static_cast<ostringstream*>( &(ostringstream() << this->puntaje) )->str();

	string puntaje("Puntaje: ");
	puntaje.append(puntos);

	return puntaje;
}