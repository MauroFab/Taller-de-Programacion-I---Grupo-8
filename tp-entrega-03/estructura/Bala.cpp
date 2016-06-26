#include "Bala.h"

Bala::Bala():ObjetoItem()
{	
	this->idOwner = -1;
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