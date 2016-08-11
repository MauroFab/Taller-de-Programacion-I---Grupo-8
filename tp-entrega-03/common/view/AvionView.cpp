#include "AvionView.h"

AvionView::AvionView()
{
	this->avionModel = NULL;
	this->spriteXml = NULL; 	
}

AvionView::AvionView(AvionModel& avionModel,SpriteXml * spriteXml)
{
	this->avionModel = avionModel;
	this->spriteXml = spriteXml;	
}

AvionView::~AvionView()
{
}
