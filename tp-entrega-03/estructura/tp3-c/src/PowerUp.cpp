#include "PowerUp.h"

PowerUp::PowerUp()
{
	this->puntaje = 0;
	this->tipo = 0;	
}
PowerUp::PowerUp(int puntaje, int tipo)
{
	this->puntaje = puntaje;
	this->tipo = tipo;	
}

PowerUp::~PowerUp()
{
}

void PowerUp::operar(AvionJugador * avionJugador,Escenario * escenario){
	if (tipo == TIPO_MUERTE){
		givePuntaje(avionJugador);
	}
	else if (tipo == TIPO_AMETRALLADORA){
		killEnemigos(escenario);
	}
	else if (tipo == TIPO_PUNTOS){
		aumentarBala(avionJugador);
	}
}
void PowerUp::givePuntaje(AvionJugador * avionJugador){
	avionJugador->takePuntaje(puntaje);
}
void PowerUp::killEnemigos(Escenario * escenario){
	AvionEnemigo * ene = NULL;
}
void PowerUp::aumentarBala(AvionJugador * avionJugador){
	avionJugador->aumentarBala();
}