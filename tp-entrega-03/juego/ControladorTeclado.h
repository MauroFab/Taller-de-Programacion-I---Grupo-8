#ifndef _CONTROLADORTECLADO_H_
#define _CONTROLADORTECLADO_H_
#include <SDL2/SDL.h>
#include <SDL2\SDL_mixer.h>
#include "Avion.h"
#include "CacheSonido.h"
#include "../common/observer/Observable.h"
#include "../common/Evento.h"

class ControladorTeclado: public Observable
{
public:
	ControladorTeclado();
	virtual ~ControladorTeclado();
	void procesarTeclasPresionadas(SDL_Event& e );
};

#endif //_CONTROLADORTECLADO_H_
