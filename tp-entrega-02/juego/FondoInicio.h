#pragma once
#ifndef _FONDOINICIO_H_
#define _FONDOINICIO_H_
#include "Textura.h"

class FondoInicio {

public:

	FondoInicio(std::string pathFondo, SDL_Renderer* renderer);
	virtual ~FondoInicio(void);

	void render();

private:

	SDL_Renderer* renderer;
	Textura* textura;
};
#endif //_FONDOINICIO_H_

