#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Etiqueta.h"

using namespace std;

class GraficadorPuntaje {

public:
	GraficadorPuntaje(SDL_Renderer* renderer);
	void renderizarPuntaje(int puntaje);
	~GraficadorPuntaje(void);

private:
	string convertirPuntajeAString();

	SDL_Renderer* renderer;
	Etiqueta* etiqueta;
	int puntaje;
};

