#pragma once
#include "Constantes.h"
#include "Textura.h"

class GraficoProyectil {

public:

	GraficoProyectil(SDL_Renderer* renderer, std::string pathProyectil, int cantFotogramas, int ancho, int alto);
	~GraficoProyectil(void);

	SDL_Rect* getCurrentClip(int frame);
	Textura* getTextura();

private:

	SDL_Rect *fotogramas;
	Textura* textura;

	int cantidadFotogramas;
};

