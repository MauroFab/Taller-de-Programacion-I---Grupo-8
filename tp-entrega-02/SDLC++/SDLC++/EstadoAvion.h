#pragma once
#include "Constantes.h"

class EstadoAvion {

public:
	
	EstadoAvion(int id, int frame, int posX, int posY);
	~EstadoAvion(void);

	int getId();
	int getFrame();
	int getPosX();
	int getPosY();

private:

	int id;
	int frame;
	int x;
	int y;
};

