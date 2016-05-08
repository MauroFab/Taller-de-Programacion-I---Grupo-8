#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "../common/observer/Observable.h"
#include "Movimiento.h"
#include "Constantes.h"

#include <map>

class Juego : public Observable
{

public:

	static Juego* getInstance();
	~Juego();

	void ejecutar();
	void close();
	std::map<int,Movimiento*> movimientosDeCompetidores;

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

