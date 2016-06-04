#include "FondoView.h"

FondoView::FondoView()
{
	this->fondoModel = NULL;
	this->spriteXml = NULL; 
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;
	this->altoFondo = 0;
}

FondoView::FondoView(FondoModel * fondoModel,SpriteXml * spriteXml)
{
	this->fondoModel = fondoModel;
	this->spriteXml = spriteXml;
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;
	this->altoFondo = 0;
}


FondoView::~FondoView()
{
}
