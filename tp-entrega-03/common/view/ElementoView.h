#ifndef _ElementoVIEW_H_
#define _ElementoVIEW_H_
/* @autor cbenez
 */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "../model/ElementoModel.h"
#include "../xml/SpriteXml.h"

class ElementoView
{
//private:
public:
	ElementoModel * elementoModel;//(COMPOSICION)
	SpriteXml * spriteXml;//(AGREGACION)
//(agregacion)referencia a la textura
	SDL_Texture * textura;
//(composicion) posicion actual de este elemento
	SDL_Rect posicion;	
public:
	ElementoView();
	ElementoView(ElementoModel * elementoModel,SpriteXml * spriteXml);
	virtual ~ElementoView();
};

#endif //_ELEMENTOVIEW_H_
