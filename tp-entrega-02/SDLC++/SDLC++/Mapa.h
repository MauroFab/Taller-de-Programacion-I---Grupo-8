#pragma once
#include "Textura.h"
#include "ElementoDelMapa.h"
class Mapa
{
public:
	Mapa(SDL_Renderer* renderer, Textura* texturaMapa, Textura* texturaIslaRecibida);
	~Mapa();
	void graficar();
	//Por ahora solo se puede crear una isla
	void crearIslaEn(int x, int y);
private:
	Textura* texturaMapa;
	Textura* texturaIsla;
	ElementoDelMapa* elementoDelMapa;
	int anchoMapa;
	int altoMapa;
	int pixelesAvanzados;
	int scrollingOffset;
	SDL_Renderer* renderer;
	int cantidadDePixelesQuePasaron;

};

