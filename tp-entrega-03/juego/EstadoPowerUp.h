#pragma once

#include <stdio.h>
#include <string.h>
#include "../common/IGenericaVO.h"

class EstadoPowerUp{
public:
	EstadoPowerUp();
	EstadoPowerUp(int tipo, bool fueUsado);

	int getTipo();
	int getPuntos();
private:
	int tipo, puntos;
	bool fueUsado;
};