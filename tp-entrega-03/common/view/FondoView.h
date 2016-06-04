#ifndef _FONDOVIEW_H_
#define _FONDOVIEW_H_
/* @autor cbenez
 */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "../model/FondoModel.h"
#include "../xml/SpriteXml.h"

class FondoView
{
//private:	
public:
	FondoModel * fondoModel;
	SpriteXml * spriteXml;
//(agregacion)referencia a la textura
	SDL_Texture * textura;
//(composicion) posicion actual
//la posicion del fondo
	SDL_Rect posicion;
	int altoFondo;
public:
	FondoView();
	FondoView(FondoModel * fondoModel,SpriteXml * spriteXml);
	virtual ~FondoView();
};

#endif //_FONDOVIEW_H_
