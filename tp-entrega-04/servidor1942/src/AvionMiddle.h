#pragma once

#include "AvionEnemigo.h"

class AvionMiddle :
	public AvionEnemigo
{
public:
	
	static const int velocidadAvionMiddle = 3;
	AvionMiddle(int x, int y);
private:
	static const int puntosDeVidaMaximoMiddle = 5;
	bool meMoviAbajoDeLaPantalla;
};