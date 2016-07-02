#pragma once

#include "AvionEnemigo.h"

class AvionMini :
	public AvionEnemigo
{
public:
	AvionMini(int x, int y);
private:
	static const int puntosDeVidaMaximoMiddle = 1;
	bool meMoviAbajoDeLaPantalla;
};