#ifndef _AVIONENEMIGOVIEW_H_
#define _AVIONENEMIGOVIEW_H_
#include "../model/AvionEnemigoModel.h"
#include "../xml/SpriteXml.h"

class AvionEnemigoView
{
public:
	AvionEnemigoModel * avionEnemigoModel;
	SpriteXml * spriteXml;
public:
	AvionEnemigoView();
	AvionEnemigoView(AvionEnemigoModel * avionEnemigoModel,SpriteXml * spriteXml);
	virtual ~AvionEnemigoView();
};

#endif //_AVIONENEMIGOVIEW_H_
