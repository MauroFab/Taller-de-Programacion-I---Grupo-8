#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "../common/observer/Observable.h"
#include "Constantes.h"

class Juego : public Observable
{

public:

	static Juego* getInstance();
	~Juego();

	void ejecutar();
	void close();
	//void agregarNuevoEstadoAvion();

private:

	static bool instanceFlag;
	static Juego* instance;
	Juego();
	bool init();
	void configuracionInicial();
	
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	void notificarMovimiento(int id, int tipo, int x, int y);
};

#endif //_JUEGO_H_

