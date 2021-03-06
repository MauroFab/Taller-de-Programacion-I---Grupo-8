#pragma once
#ifndef _GRAFICOPROYECTIL_H_
#define _GRAFICOPROYECTIL_H_

#include <stdio.h>
#include "Textura.h"
#include "../common/view/BalaView.h"

class GraficoProyectil {

public:

	GraficoProyectil(SDL_Renderer* renderer, BalaView * balaView);
	~GraficoProyectil(void);

	SDL_Rect* getCurrentClip(int frame);
	Textura* getTextura();

private:

	SDL_Rect *fotogramas;
	Textura* textura;

	int cantidadFotogramas;
};
#endif //_GRAFICOPROYECTIL_H_
