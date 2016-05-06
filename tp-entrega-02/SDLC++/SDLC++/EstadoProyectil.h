#pragma once
#include "Constantes.h"

class EstadoProyectil {

public:

	EstadoProyectil(int frame, int posX, int posY);
	~EstadoProyectil(void);

	int getFrame();
	int getPosX();
	int getPosY();

private:

	int frame;
	int x;
	int y;
};

