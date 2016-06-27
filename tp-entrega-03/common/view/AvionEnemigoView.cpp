#include "AvionEnemigoView.h"

AvionEnemigoView::AvionEnemigoView()
{
	this->avionEnemigoModel = NULL;
	this->spriteXml = NULL;
}
AvionEnemigoView::AvionEnemigoView(AvionEnemigoModel * avionEnemigoModel,SpriteXml * spriteXml){
	this->avionEnemigoModel = avionEnemigoModel;
	this->spriteXml = spriteXml;
}

AvionEnemigoView::~AvionEnemigoView()
{
	if (this->avionEnemigoModel != NULL){
		delete this->avionEnemigoModel;
	}
}
