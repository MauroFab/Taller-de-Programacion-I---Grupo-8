#include "BalaEnemigo.h"

BalaEnemigo::BalaEnemigo()
{
	life_time = 1000;
}

BalaEnemigo::~BalaEnemigo()
{
}
void BalaEnemigo::update() {
	BalaEnemigo * loc1 = this;
	int loc2 = ((loc1 = this)->life_time - 1);
	loc1->life_time = loc2;
	if (this->life_time < 0) {
		kill();
	}
	/*
	if (Level->plane != NULL && this->overlaps_rectanble_bis(Level->plane)) {
		this->kill();
		Level->plane->dead = true;
	}
	*/
	Bala::update();
	return;
}
