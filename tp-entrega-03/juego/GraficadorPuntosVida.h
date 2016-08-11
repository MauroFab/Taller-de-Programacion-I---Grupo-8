#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Etiqueta.h"

using namespace std;

class GraficadorPuntosVida {

public:
	GraficadorPuntosVida(SDL_Renderer* renderer);
	virtual ~GraficadorPuntosVida(void);
	void renderizarPuntosDeVida(int puntosDeVida);

private:
	string convertirPuntajeAString();

	SDL_Renderer* renderer;
	Etiqueta* etiqueta;
	int puntosDeVida;
};