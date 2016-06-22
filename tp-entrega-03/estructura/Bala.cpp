#include "Bala.h"

Bala::Bala():ObjetoItem()
{
	this->bMuerto = false;
	this->idOwner = -1;
    this->existe = true;
    this->activo = true;
    this->visible = true;
}

Bala::~Bala()
{
}

void Bala::update(){
	ObjetoItem::update();
}
void Bala::kill(){
    this->existe = false;
    this->bMuerto = true;
    return;
}
void Bala::render(){
	ObjetoItem::render();
    return;
}