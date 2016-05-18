#include "ElementoView.h"

ElementoView::ElementoView()
{
	this->elementoModel = NULL;
	this->spriteXml = NULL; 
	this->textura = NULL;
	this->posicion.x = -1;
	this->posicion.y = -1;
	this->posicion.w = 0;
	this->posicion.h = 0;	
}
ElementoView::ElementoView(ElementoModel * elementoModel,SpriteXml * spriteXml){
	this->elementoModel = elementoModel; 
	this->spriteXml = spriteXml;
	this->textura = NULL;
	this->posicion.x = elementoModel->posicion.coorX;
	this->posicion.y = elementoModel->posicion.coorY;
	this->posicion.w = 0;
	this->posicion.h = 0;	
}

ElementoView::~ElementoView()
{
	if (this->elementoModel != NULL){
		delete this->elementoModel;
	}
	
}
