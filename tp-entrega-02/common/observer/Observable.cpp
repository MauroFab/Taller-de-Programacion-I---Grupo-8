#include "Observable.h"

using namespace std;

Observable::Observable() {
}

Observable::~Observable() {
}

void Observable::agregarObservador(Observador* obs) {
	//SDL_mutexP(mut);
	this->observables.push_back(obs);
	//SDL_mutexV(mut);
}

void Observable::notificar(int argc, void* argv[]) {

	//SDL_mutexP(mut);

	vector<Observador*>::iterator it;
	for (it = this->observables.begin(); it != this->observables.end(); it++) {
		(*it)->actualizar(argc, argv);
	}

	//SDL_mutexV(mut);
}

