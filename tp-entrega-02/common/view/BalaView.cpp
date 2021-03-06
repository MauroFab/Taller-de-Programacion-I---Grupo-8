#include "BalaView.h"

BalaView::BalaView()
{
	this->balaModel = NULL; 
	this->spriteXml = NULL; 
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;
	this->activa = false;	
}
BalaView::BalaView(BalaModel * balaModel,SpriteXml * spriteXml){
	this->balaModel = balaModel; 
	this->spriteXml = spriteXml; 
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;
	this->activa = false;
}
BalaView::~BalaView()
{
	//solo se libera el model
	if (this->balaModel != NULL){
		delete this->balaModel;
	}
}
