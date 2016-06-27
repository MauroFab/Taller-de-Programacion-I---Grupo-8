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
bool PowerUp::esDeAmetralladora(){
	return (tipo == TIPO_AMETRALLADORA);
}

bool PowerUp::esDeMuerte(){
	return (tipo == TIPO_MUERTE);
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
	int x = superficieOcupada.obtenerPosicion().getPosX();
	int y = superficieOcupada.obtenerPosicion().getPosY();
	return(EstadoPowerUp(tipo,usado,x,y));
}

void PowerUp::continuarMovimiento(){
	this->superficieOcupada.desplazarEnYObteniendoHitbox(-1);
}