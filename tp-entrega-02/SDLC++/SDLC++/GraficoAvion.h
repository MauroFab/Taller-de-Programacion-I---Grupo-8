#pragma once
#include "Constantes.h"
#include "Textura.h"

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


