#include "FondoInicio.h"


FondoInicio::FondoInicio(std::string pathFondo, SDL_Renderer* renderer) {

	this->renderer = renderer;

	textura = new Textura();
	textura->cargarDeArchivo(pathFondo, renderer);
}

FondoInicio::~FondoInicio(void) {

	textura->liberar();
	delete textura;
}

void FondoInicio::render() {

	textura->render(0, 0, renderer);
}