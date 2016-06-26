#include "EstadoPowerUp.h"

EstadoPowerUp::EstadoPowerUp(){

}

EstadoPowerUp::EstadoPowerUp(int tipo, bool fueUsado, int x, int y){
	this->tipo = tipo;
	this->fueUsado = fueUsado;
	this->x = x;
	this->y = y;
}

int EstadoPowerUp::getTipo(){
	return tipo;
}

bool EstadoPowerUp::fueUsadoElPowerUp(){
	return fueUsado;
}

int EstadoPowerUp::getX(){
	return x;
}

int EstadoPowerUp::getY(){
	return y;
}