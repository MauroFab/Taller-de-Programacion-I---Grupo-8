#pragma once
#include "Textura.h"

class Mapa
{
public:
	Mapa(SDL_Renderer* renderer, Textura* texturaMapa);
	~Mapa();
	void graficar();
private:
	Textura* texturaMapa;
	int anchoMapa;
	int altoMapa;
	int pixelesAvanzados;
	int scrollingOffset;
	SDL_Renderer* renderer;
};

