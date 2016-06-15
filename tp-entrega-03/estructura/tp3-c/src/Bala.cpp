#include "Bala.h"

Bala::Bala()
{
	bMuerto = false;
	idOwner = -1;
}

Bala::~Bala()
{
}
void Bala::morir(){
	bMuerto = true;
}