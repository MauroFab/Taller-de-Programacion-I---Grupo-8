#ifndef _AVION_SECUNDARIO_H
#define _AVION_SECUNDARIO_H

#include "SuperficieOcupada.h"

#define ALTO 40
#define ANCHO 24

class AvionSecundario {

public:
	AvionSecundario();
	virtual ~AvionSecundario();

	bool esVisible();
	void hacerVisible();
	void setPosicion(int x, int y);
	int getAncho();
	int getAlto();

private:
	bool visible;
	SuperficieOcupada* superficieOcupada;
};

#endif _AVION_SECUNDARIO_H