#pragma once
#include "fakeavionenemigo.h"
class FakeAvionMiddle :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionMiddle = 3;
	FakeAvionMiddle(int x, int y);
private:
	static const int puntosDeVidaMaximoMiddle = 5;
	bool meMoviAbajoDeLaPantalla;
};