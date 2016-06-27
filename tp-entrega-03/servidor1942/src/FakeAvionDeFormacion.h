#pragma once
#include "fakeavionenemigo.h"
class FakeAvionDeFormacion :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionMini = 2;
	FakeAvionDeFormacion(int y, int alturaDeLaQueSale);
	void continuarMovimiento();
private:
	//vienen desde la derecha y desde afuera

	static const int xInicial = 500;
	static const int puntosDeVidaMaximoMini = 1;
	int alturaDeLaQueSalgo;
	bool listoParaSalir;
};

