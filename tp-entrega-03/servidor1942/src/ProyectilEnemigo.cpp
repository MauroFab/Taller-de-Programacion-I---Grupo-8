#include "ProyectilEnemigo.h"


ProyectilEnemigo::ProyectilEnemigo(int x, int y, double velocidadX,double velocidadY){
	this->superficieQueOcupo = SuperficieOcupada(x,y,anchoBala,altoBala);
	velocidadEnX = velocidadX;
	velocidadEnY = velocidadY;
	posX = x;
	posY = y;
}


ProyectilEnemigo::~ProyectilEnemigo(void){
}

void ProyectilEnemigo::mover(){
	this->posX = posX + velocidadEnX;
	this->posY = posY + velocidadEnY;
	int xInt, yInt;
	superficieQueOcupo.moverAPosicionXObteniendoHitbox(posX);
	superficieQueOcupo.moverAPosicionXObteniendoHitbox(posY);
}
