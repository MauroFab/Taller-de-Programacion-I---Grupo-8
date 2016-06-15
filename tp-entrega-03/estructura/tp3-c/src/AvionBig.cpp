#include "AvionBig.h"

AvionBig::AvionBig()
{
}

AvionBig::~AvionBig()
{
}
PowerUp * AvionBig::createPowerUp(){
	return new PowerUp();
}

void AvionBig::disparar(){
	dispararMultiple();
}

void AvionBig::dispararMultiple(){
	
}