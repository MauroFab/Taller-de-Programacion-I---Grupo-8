#pragma once

#include "AvionEnemigo.h"

class AvionBig :
	public AvionEnemigo
{
public:
	
	static const int velocidadAvionBig = 2;
	AvionBig(int x, int y);
	void continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores);
	bool dejaUnPowerUpAlSerDestruido();
	//No llamar si dejaUnPowerUpAlSerDestruido indica false
	PowerUp getPowerUpQueDejaAlSerDestruido();

	void disparar();
private:
	static const int puntosDeVidaMaximoBig = 10;
	bool meMoviAbajoDeLaPantalla;
};

