#include "AvionView.h"

AvionView::AvionView()
{
	this->avionModel = NULL;
	this->spriteXml = NULL; 
/*
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;	
*/	
}
AvionView::AvionView(AvionModel * avionModel,SpriteXml * spriteXml)
{
	this->avionModel = avionModel;
	this->spriteXml = spriteXml;
/*
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;	
*/	
}

AvionView::~AvionView()
{
	//solo se libera el model
	if (this->avionModel != NULL){
		delete this->avionModel;
	}
}
