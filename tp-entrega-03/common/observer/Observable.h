#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>
#include <SDL2/SDL.h>
#include "Observador.h"
#include "../Evento.h"
class Observable {

private:
	std::vector<Observador*> observadores;
	SDL_mutex *mutObs; // mutex para proteger la lista de Observadores

public:
	Observable();
	void agregarObservador(Observador* obs);
	int notificar(Evento* evento);
	virtual ~Observable();
};

#endif /* OBSERVABLE_H_ */

