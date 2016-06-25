#include "PowerUp.h"

PowerUp::PowerUp()
{
	this->puntos = 0;
	this->tipo = 0;	
	superficieOcupada = NULL;
	usado = false;
}

PowerUp::PowerUp(int p_x,int p_y,int puntos, int tipo)
{
	superficieOcupada = new SuperficieOcupada(p_x,p_y,ANCHO,ALTO);
	this->puntos = puntos;
	this->tipo = tipo;	
	usado = false;
}

bool PowerUp::esDePuntos(){
	return (tipo == TIPO_PUNTOS);
}
PowerUp::~PowerUp(){
	//delete superficieOcupada;
}

bool PowerUp::fueUsado(){
	return usado;
}
void PowerUp::marcarComoUsado(){
	usado = true;
}

SuperficieOcupada PowerUp::obtenerSuperficieOcupada(){
	return *superficieOcupada;
}

int PowerUp::obtenerPuntosQueOtorga(){
	return puntos;
}