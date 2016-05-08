#pragma once
#include "Constantes.h"
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

