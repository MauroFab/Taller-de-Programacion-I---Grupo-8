#include "AvionEnemigo.h"

AvionEnemigo::AvionEnemigo()
{
	this->energiaInicial = 0;
	this->energia = 0;
	this->valorPuntaje = 0;
	this->trayectoria = 0;
}

AvionEnemigo::~AvionEnemigo()
{
}
int AvionEnemigo::givePuntos(){
	return valorPuntaje;
}

void AvionEnemigo::reduceEnergia(int deltaEnergia){
	this->energia -= deltaEnergia;
}

void AvionEnemigo::disparar(){
	
}