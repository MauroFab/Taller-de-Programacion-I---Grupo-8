#ifndef _AVIONVIEW_H_
#define _AVIONVIEW_H_
/* @autor cbenez
 */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "../model/AvionModel.h"
#include "../xml/SpriteXml.h"

class AvionView
{
//private:	
public:
	AvionModel * avionModel;
	SpriteXml * spriteXml;
//(agregacion)referencia a la textura
	SDL_Texture * textura;
//(composicion) posicion actual de este elemento
	SDL_Rect posicion;		
public:
	AvionView();
	AvionView(AvionModel * avionModel,SpriteXml * spriteXml);
	virtual ~AvionView();
};

#endif //_AVIONVIEW_H_
