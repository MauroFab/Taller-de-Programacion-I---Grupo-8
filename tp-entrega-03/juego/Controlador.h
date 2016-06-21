#pragma once

#include <SDL2/SDL.h>
#include <SDL2\SDL_mixer.h>
#include "Avion.h"
#include "CacheSonido.h"
#include "../common/observer/Observable.h"
#include "../common/Evento.h"

class Controlador: public Observable {

public:
	Controlador();
	~Controlador();
	void procesarTeclasPresionadas(SDL_Event& e );
};
