#ifndef _BalaVIEW_H_
#define _BalaVIEW_H_
/* @autor cbenez
 */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "../model/BalaModel.h"
#include "../xml/SpriteXml.h"
class BalaView
{
//private:
public:
	BalaModel balaModel;
	SpriteXml * spriteXml;
//(agregacion)referencia a la textura
	SDL_Texture * textura;
//(composicion) posicion actual de este elemento
	SDL_Rect posicion;
//indicador de bala activa o inactiva
	bool activa;
	
public:
	BalaView();
	BalaView(const BalaView& b):balaModel(b.balaModel),spriteXml(b.spriteXml){};
	void BalaView::operator=(const BalaView &b){this->balaModel=b.balaModel; this->spriteXml=b.spriteXml;};
	BalaView(BalaModel& balaModel,SpriteXml * spriteXml);
	virtual ~BalaView();
};

#endif //_BALAVIEW_H_
