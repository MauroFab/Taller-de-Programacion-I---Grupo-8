#include "AvionEnemigo.h"

AvionEnemigo::AvionEnemigo():ObjetoItem()
{
	this->energiaInicial = 0;
	this->energia = 1;
	this->puntos = 0;
	this->trayectoria.coorX = 0;
	this->trayectoria.coorY = 0;
	this->bMuerto = false;
	this->bEnMuerte = false;
	this->bUnaVez = true;
}
AvionEnemigo::AvionEnemigo(int p_x,int p_y):ObjetoItem(){
	this->x = p_x;
	this->y = p_y;
	this->energiaInicial = 0;
	this->energia = 1;
	this->puntos = 0;
	this->trayectoria.coorX = 0;
	this->trayectoria.coorY = 0;
	this->bMuerto = false;
	this->bEnMuerte = false;
	this->bUnaVez = true;
}

AvionEnemigo::~AvionEnemigo()
{
}
int AvionEnemigo::givePuntos(){
	return puntos;
}

void AvionEnemigo::reduceEnergia(int deltaEnergia){
	this->energia -= deltaEnergia;
}

BalaEnemigo * AvionEnemigo::disparar(){
	return NULL;
}
void AvionEnemigo::update(){
	if (this->energia <= 0){
		this->bMuerto = true;
	}
	if (bMuerto && this->bEnMuerte){
		this->bEnMuerte = false;
//		SpriteAvion::play("kill")
	}
	ObjetoItem::update();
	
}