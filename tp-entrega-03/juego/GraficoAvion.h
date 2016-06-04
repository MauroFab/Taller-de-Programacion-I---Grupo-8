#pragma once
#ifndef _GRAFICOAVION_H_
#define _GRAFICOAVION_H_

#include "Textura.h"
#include "../common/view/AvionView.h"

//**************************
//Esto NOO debe estar
#define FAKE_PATH_AVION_NOT_ENC "avionNoEncontrado.bmp"
//**************************
class GraficoAvion {
public:
	GraficoAvion(SDL_Renderer* renderer, AvionView * avionView);
	~GraficoAvion(void);
	SDL_Rect* getCurrentClip(int frame);
	Textura* getTextura();
private:
	SDL_Rect *fotogramas;
	Textura* textura;
	int id;
	int cantidadFotogramas;
};

#endif //_GRAFICOAVION_H_
