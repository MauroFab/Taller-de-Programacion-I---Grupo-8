#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>

#include "TexturaFuente.h"
#include <string>

class Etiqueta {

public:
	Etiqueta(SDL_Renderer* renderer, TTF_Font* font, std::string texto);
	Etiqueta(SDL_Renderer* renderer, TTF_Font* font);
	Etiqueta(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	virtual ~Etiqueta(void);

	void setTexto(std::string texto);
	void setPosicion(int x, int y);
	void render();
	void limpiar();

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;
	std::string texto;
	TexturaFuente* textura;
	int posX;
	int posY;
};

