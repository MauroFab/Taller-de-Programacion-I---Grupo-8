#pragma once

#include <SDL2/SDL.h>
#include "../Avion.h"

class Controlador
{
public:
	Controlador(Avion* avion);
	~Controlador();
	void procesarTeclasPresionadas(SDL_Event& e );
private:
	Avion* avion;
};

