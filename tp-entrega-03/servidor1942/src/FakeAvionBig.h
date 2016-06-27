#pragma once
#include "fakeavionenemigo.h"
class FakeAvionBig :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionBig = 2;
	FakeAvionBig(int x, int y);
	void continuarMovimiento();
private:
	static const int puntosDeVidaMaximoBig = 5;
	bool meMoviAbajoDeLaPantalla;
};

