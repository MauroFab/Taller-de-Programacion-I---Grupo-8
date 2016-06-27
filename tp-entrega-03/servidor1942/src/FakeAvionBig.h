#pragma once
#include "FakeAvionEnemigo.h"
class FakeAvionBig :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionBig = 2;
	FakeAvionBig(int x, int y);
	void continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores);
	bool dejaUnPowerUpAlSerDestruido();
	//No llamar si dejaUnPowerUpAlSerDestruido indica false
	PowerUp getPowerUpQueDejaAlSerDestruido();
private:
	static const int puntosDeVidaMaximoBig = 10;
	bool meMoviAbajoDeLaPantalla;
};

