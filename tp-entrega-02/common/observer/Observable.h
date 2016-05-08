#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>
#include <SDL2/SDL.h>
#include "Observador.h"

class Observable {

private:
	std::vector<Observador*> observables;
	SDL_mutex *mut; // mutex para proteger la lista de Observadores

public:
	Observable();
	void agregarObservador(Observador* obs);
	void notificar(int argc, void* argv[]);
	virtual ~Observable();
};

#endif /* OBSERVABLE_H_ */

