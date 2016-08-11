#ifndef _AVIONVIEW_H_
#define _AVIONVIEW_H_
/* @autor cbenez
 */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "../model/AvionModel.h"
#include "../xml/SpriteXml.h"

class AvionView {

public:
	AvionModel avionModel;
	SpriteXml * spriteXml;	
public:
	AvionView();
	AvionView(const AvionView& b):avionModel(b.avionModel),spriteXml(b.spriteXml){};
	void AvionView::operator=(const AvionView &b){this->avionModel=b.avionModel; this->spriteXml=b.spriteXml;};
	AvionView(AvionModel& avionModel,SpriteXml * spriteXml);
	~AvionView();
};

#endif //_AVIONVIEW_H_
