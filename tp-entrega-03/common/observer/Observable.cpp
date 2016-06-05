#include "Observable.h"

using namespace std;

Observable::Observable() {
	mutObs = SDL_CreateMutex();
}

Observable::~Observable() {
	SDL_DestroyMutex(mutObs);
}

void Observable::agregarObservador(Observador* obs) {

	SDL_mutexP(mutObs);
	this->observadores.push_back(obs);
	SDL_mutexV(mutObs);
}

int Observable::notificar(void* argv[]) {

	SDL_mutexP(mutObs);
	int estado=0;
	vector<Observador*>::iterator it;
	for (it = this->observadores.begin(); it != this->observadores.end(); it++) {
		
		if((*it)->actualizar(argv)<0)
		estado=-1;
	}
	SDL_mutexV(mutObs);
	return estado;
}

