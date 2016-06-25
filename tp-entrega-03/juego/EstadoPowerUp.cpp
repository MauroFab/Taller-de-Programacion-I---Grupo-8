#include "EstadoPowerUp.h"

EstadoPowerUp::EstadoPowerUp(){

}

EstadoPowerUp::EstadoPowerUp(int tipo, bool fueUsado){
	this->tipo = tipo;
	this->fueUsado = fueUsado;
}