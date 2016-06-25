#include "PowerUp.h"

PowerUp::PowerUp()
{
	this->puntos = 0;
	this->tipo = 0;	
	usado = false;
}

PowerUp::PowerUp(int p_x,int p_y,int puntos, int tipo)
{
	superficieOcupada = SuperficieOcupada(p_x,p_y,ANCHO,ALTO);
	this->puntos = puntos;
	this->tipo = tipo;	
	usado = false;
}

bool PowerUp::esDePuntos(){
	return (tipo == TIPO_PUNTOS);
}
PowerUp::~PowerUp(){
}

bool PowerUp::fueUsado(){
	return usado;
}
void PowerUp::marcarComoUsado(){
	usado = true;
}

SuperficieOcupada PowerUp::obtenerSuperficieOcupada(){
	return superficieOcupada;
}

int PowerUp::obtenerPuntosQueOtorga(){
	return puntos;
}

EstadoPowerUp PowerUp::getEstado(){ 
	return(EstadoPowerUp(tipo,usado));
}