#pragma once

const int TIPO_MUERTE = 10;
const int TIPO_AMETRALLADORA = 11;
const int TIPO_PUNTOS = 12;

#include <stdio.h>

class EstadoPowerUp{
public:
	EstadoPowerUp();
	EstadoPowerUp(int tipo, bool fueUsado);
	int getTipo();
	bool fueUsadoElPowerUp();
	
private:
	int tipo;
	bool fueUsado;
};