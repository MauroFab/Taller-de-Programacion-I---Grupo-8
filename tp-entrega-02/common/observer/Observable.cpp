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
	this->observables.push_back(obs);
	SDL_mutexV(mutObs);
}

void Observable::notificar(void* argv[]) {

	SDL_mutexP(mutObs);

	vector<Observador*>::iterator it;
	for (it = this->observables.begin(); it != this->observables.end(); it++) {
		(*it)->actualizar(argv);
	}

	SDL_mutexV(mutObs);
}

