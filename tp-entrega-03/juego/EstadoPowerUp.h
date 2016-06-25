#pragma once

#include <stdio.h>

class EstadoPowerUp{
public:
	EstadoPowerUp();
	EstadoPowerUp(int tipo, bool fueUsado);

	int getTipo();
	int getPuntos();
private:
	int tipo;
	bool fueUsado;
};