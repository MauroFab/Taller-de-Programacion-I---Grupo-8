#include "AvionJugador.h"

AvionJugador::AvionJugador():ObjetoItem()
{
	energia = 1;
	bUnaVez = true;
}
AvionJugador::AvionJugador(int p_x,int p_y):ObjetoItem(){
	this->x = p_x;
	this->y = p_y;
	energia = 1;
	bUnaVez = true;
}

AvionJugador::~AvionJugador()
{
}
bool AvionJugador::sinEquipo(){
	return this->idEquipo == -1;
}

BalaJugador * AvionJugador::aumentarBala(){
	return new BalaJugador();
}
void AvionJugador::takePuntaje(int puntaje){
	this->puntaje += puntaje;
}

void AvionJugador::morir(){
	bMuerto = true;
}
void AvionJugador::update(){
	if (this->energia <= 0){
		this->bMuerto = true;
	}	
	if (bMuerto) {
		if(bUnaVez){
//			play("die");
			this->bUnaVez = false;
		}
	}
	ObjetoItem::update();
}