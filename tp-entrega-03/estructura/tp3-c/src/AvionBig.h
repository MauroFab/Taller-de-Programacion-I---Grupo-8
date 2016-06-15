#ifndef _AVIONBIG_H_
#define _AVIONBIG_H_

#include "AvionEnemigo.h"
#include "PowerUp.h"

class AvionBig : public AvionEnemigo
{
public:
	AvionBig();
	virtual ~AvionBig();
	PowerUp * createPowerUp();
	void disparar();
	void dispararMultiple();
};

#endif //_AVIONBIG_H_
