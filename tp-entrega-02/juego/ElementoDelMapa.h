#pragma once
#include "Textura.h"
class ElementoDelMapa
{
public:
	ElementoDelMapa(int xInicial, int yInicial, SDL_Renderer* gRenderer, Textura* textura);
	~ElementoDelMapa(void);
	void graficarseSiEstaEnPantalla(int yMaxPantalla,int  yMinPantalla);
	void reiniciar();
private:
	bool apareceDesdeAfuera(int yMaxPantalla, int yMinPantalla);
	bool estaEnPantalla(int yMaxPantalla,int  yMinPantalla);
	int x;
	int y;
	int yInicialParaGraficar;
	int offset;
	SDL_Renderer* gRenderer;
	Textura* textura;
};

