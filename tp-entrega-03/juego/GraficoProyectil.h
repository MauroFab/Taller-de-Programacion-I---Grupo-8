#pragma once
#ifndef _GRAFICOPROYECTIL_H_
#define _GRAFICOPROYECTIL_H_

#include <stdio.h>
#include "Textura.h"
#include "../common/view/BalaView.h"

class GraficoProyectil {
private:
	SDL_Rect *fotogramas;
	Textura* textura;
	int id;
	int cantidadFotogramas;

public:

	GraficoProyectil(SDL_Renderer* renderer, BalaView * balaView);
	~GraficoProyectil(void);

	SDL_Rect* getCurrentClip(int frame);
	Textura* getTextura();
};
#endif //_GRAFICOPROYECTIL_H_
