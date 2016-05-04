#pragma once

#include "Constantes.h"
#include "Textura.h"
#include "Mapa.h"
#include "Avion.h"

class Proyectil {

public:

	//The dimensions of the dot
	static const int DOT_WIDTH = 47;
	static const int DOT_HEIGHT = 44;

	static const int DOT_VEL = 1;

	Proyectil(SDL_Renderer* rendererRecibido, std::string dirImagenProyectil, int cantidadDeFrames, int anchoFotograma, int altoFotograma);

	virtual ~Proyectil(void);

	void move();

	void render();

	void setCoordenasDeComienzo(int posX, int posY);

private:

	SDL_Rect *fotogramas;
	Textura* texturaProyectil;
	SDL_Renderer* renderer;
	int frame;
	int cantDeFotogramas;

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};

