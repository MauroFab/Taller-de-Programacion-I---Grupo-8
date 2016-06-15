#include "AvionJugador.h"

AvionJugador::AvionJugador()
{
}

AvionJugador::~AvionJugador()
{
}
bool AvionJugador::sinEquipo(){
	return this->idEquipo == -1;
}

void AvionJugador::aumentarBala(){
	
}
void AvionJugador::takePuntaje(int puntaje){
	this->puntaje += puntaje;
}

void AvionJugador::morir(){
	bMuerto = true;
}	