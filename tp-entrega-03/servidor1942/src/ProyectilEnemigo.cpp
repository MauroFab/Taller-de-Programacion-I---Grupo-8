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
	this->posY = (posY + velocidadEnY);
	superficieQueOcupo.moverAPosicionXObteniendoHitbox(static_cast<int>(posX));
	superficieQueOcupo.moverAPosicionXObteniendoHitbox(static_cast<int>(posY));
}

EstadoProyectil* ProyectilEnemigo::createEstado(){
	int intX = static_cast<int>(posX);
	int intY = static_cast<int>(posY);
	//Los proyectiles enemigos son siempre los basicos
	bool mejorado = false;
	bool visible = true;
	int frame = 0;
	return (new EstadoProyectil(frame,intX,intY,mejorado,visible));
}
