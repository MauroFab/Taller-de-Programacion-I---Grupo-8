#pragma once

const int TIPO_MUERTE = 10;
const int TIPO_AMETRALLADORA = 11;
const int TIPO_PUNTOS = 12;

#include <stdio.h>

class EstadoPowerUp{
public:
	EstadoPowerUp();
	EstadoPowerUp(int tipo, bool fueUsado, int x, int y);
	int getTipo();
	bool fueUsadoElPowerUp();
	int getX();
	int getY();
	
private:
	int tipo;
	int x;
	int y;
	bool fueUsado;
};