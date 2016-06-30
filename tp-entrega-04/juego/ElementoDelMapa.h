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
	bool apareceDesdeAfuera(int yMaxPantalla, int yMinPantalla);
	bool estaEnPantalla(int yMaxPantalla,int  yMinPantalla);
	bool aparezcoDesdeAfuera;
	int posicionInicialPantalla;
	int x;
	int y;
	int yInicialParaGraficar;
	bool meHanGraficadoAlgunaVez;
	SDL_Renderer* gRenderer;
	Textura* textura;
};
#endif //_ELEMENTODELMAPA_H_
