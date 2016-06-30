#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <stdlib.h>

#include "TexturaFuente.h"
#include <string>

class TextField {

public:
	TextField(SDL_Renderer* renderer, TTF_Font* font);
	virtual ~TextField(void);

	std::string getTexto();
	void setPosicion(int x, int y);
	void manejarEvento(SDL_Event evento);
	void render();
	void limpiar();
	bool contieneLetras();

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;
	std::string texto;
	bool renderTextFlag;
	TexturaFuente* textura;
	int posX;
	int posY;
};

