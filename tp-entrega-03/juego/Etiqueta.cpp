#include "Etiqueta.h"

Etiqueta::Etiqueta(SDL_Renderer* renderer, TTF_Font* font) {

	this->renderer = renderer;
	this->font = font;
	SDL_Color textColor = { 0, 0, 0, 0 };
	this->color = textColor;
	this->textura = new TexturaFuente();
}

Etiqueta::Etiqueta(SDL_Renderer* renderer, TTF_Font* font, std::string texto) {

	this->renderer = renderer;
	this->font = font;
	this->texto = texto;
	SDL_Color textColor = { 0, 0, 0, 0 };
	this->color = textColor;
	this->textura = new TexturaFuente();
	this->textura->loadFromRenderedText(this->font, this->renderer, this->texto, this->color);
}

Etiqueta::~Etiqueta(void) {
	this->textura->free();
}

void Etiqueta::setTexto(std::string texto) {
	this->texto = texto;
	this->textura->loadFromRenderedText(this->font, this->renderer, this->texto, this->color);
}

void Etiqueta::setPosicion(int x, int y) {
	this->posX = x;
	this->posY = y;
}

void Etiqueta::render() {
	this->textura->render(this->renderer, this->posX, this->posY);
}

void Etiqueta::limpiar() {
	this->texto.assign("");
}