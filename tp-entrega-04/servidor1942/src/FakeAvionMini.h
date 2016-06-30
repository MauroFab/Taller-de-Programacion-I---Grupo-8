#pragma once
#include "fakeavionenemigo.h"
class FakeAvionMini :
	public FakeAvionEnemigo
{
public:
	FakeAvionMini(int x, int y);
private:
	static const int puntosDeVidaMaximoMiddle = 1;
	bool meMoviAbajoDeLaPantalla;
};