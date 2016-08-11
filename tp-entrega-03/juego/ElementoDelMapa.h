#pragma once
#ifndef _ELEMENTODELMAPA_H_
#define _ELEMENTODELMAPA_H_
#include "Textura.h"
class ElementoDelMapa
{
public:
	ElementoDelMapa(int xInicial, int yInicial, SDL_Renderer* gRenderer, Textura* textura);
	~ElementoDelMapa(void);
	void graficarseSiEstaEnPantalla(int yMaxPantalla,int  yMinPantalla);
	void reiniciar();
private:
	bool estaEnPantalla(int yMaxPantalla,int  yMinPantalla);
	int x;
	int y;
	SDL_Renderer* gRenderer;
	Textura* textura;
};
#endif //_ELEMENTODELMAPA_H_
