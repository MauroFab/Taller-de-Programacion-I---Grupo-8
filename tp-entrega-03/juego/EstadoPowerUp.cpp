#include "EstadoPowerUp.h"

EstadoPowerUp::EstadoPowerUp(){

}

EstadoPowerUp::EstadoPowerUp(int tipo, bool fueUsado){
	this->tipo = tipo;
	this->fueUsado = fueUsado;
}

int EstadoPowerUp::getTipo(){
	return tipo;
}

bool EstadoPowerUp::fueUsadoElPowerUp(){
	return fueUsado;
}