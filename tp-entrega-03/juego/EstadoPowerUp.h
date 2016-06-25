#pragma once

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