#pragma once
#ifndef _GRAFICOAVION_H_
#define _GRAFICOAVION_H_

#include "Textura.h"

//**************************
//Esto NOO debe estar
#define FAKE_PATH_AVION_NOT_ENC "avionNoEncontrado.bmp"
//**************************

class GraficoAvion {

public:

	GraficoAvion(SDL_Renderer* renderer, int id, std::string pathAvion, int cantFotogramas, int ancho, int alto);
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
