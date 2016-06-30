#include "PowerUp.h"

PowerUp::PowerUp():ObjetoItem()
{
	this->puntos = 0;
	this->tipo = 0;	
}
PowerUp::PowerUp(int puntos, int tipo)
{
	this->x = -1;
	this->y = -1;	
	this->puntos = puntos;
	this->tipo = tipo;	
}
PowerUp::PowerUp(int p_x,int p_y,int puntos, int tipo)
{
	this->x = p_x;
	this->y = p_y;	
	this->puntos = puntos;
	this->tipo = tipo;	
}

PowerUp::~PowerUp()
{
}

void PowerUp::operar(AvionJugador * avionJugador,Escenario * escenario){
	if (tipo == TIPO_MUERTE){
		givePuntos(avionJugador);
	}
	else if (tipo == TIPO_AMETRALLADORA){
		killEnemigos(escenario);
	}
	else if (tipo == TIPO_PUNTOS){
		aumentarBala(avionJugador);
	}
}
void PowerUp::givePuntos(AvionJugador * avionJugador){
	avionJugador->takePuntaje(puntos);
}
void PowerUp::killEnemigos(Escenario * escenario){
	AvionEnemigo * ene = NULL;
}
void PowerUp::aumentarBala(AvionJugador * avionJugador){
	avionJugador->aumentarBala();
}