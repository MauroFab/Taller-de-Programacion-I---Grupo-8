#ifndef _AVIONBIG_H_
#define _AVIONBIG_H_

#include "AvionEnemigo.h"
#include "PowerUp.h"
#include "Escenario.h"
class Escenario;
class AvionBig : public AvionEnemigo
{
public:
	Escenario * pEscenario;
	int puntos_derribo;
	int puntos_solo;
public:
	AvionBig();
	AvionBig(Escenario * escenario);
	AvionBig(int p_x,int p_y);
	AvionBig(Escenario * escenario,int p_x,int p_y);
	virtual ~AvionBig();
	PowerUp * createPowerUp();
	BalaEnemigo * disparar();
	BalaEnemigo * dispararMultiple();
	void update();
};

#endif //_AVIONBIG_H_
