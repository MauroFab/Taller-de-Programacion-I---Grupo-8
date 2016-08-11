#pragma once
#ifndef _FONDOINICIO_H_
#define _FONDOINICIO_H_
#include "Textura.h"

class FondoInicio {
private:
	SDL_Renderer* renderer;
	Textura* textura;

public:

	FondoInicio(std::string pathFondo, SDL_Renderer* renderer);
	virtual ~FondoInicio(void);
	void render();
};
#endif //_FONDOINICIO_H_