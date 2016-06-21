#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <stdio.h>
#include <string.h>
class GraficadorPuntaje
{
public:
	GraficadorPuntaje();
	void renderizarPuntaje(SDL_Renderer* renderer,int puntaje);
	~GraficadorPuntaje(void);
};

