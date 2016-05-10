#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "../common/observer/Observable.h"
#include "Movimiento.h"
#include "Constantes.h"

#include <SDL2/SDL.h>
#include <map>

class Juego : public Observable
{

public:

	static Juego* getInstance();
	~Juego();

	void ejecutar();
	void close();
	void actualizarMovimientos(Movimiento* movimiento);

private:

	static bool instanceFlag;
	static Juego* instance;
	Juego();
	bool init();
	void configuracionInicial();
	
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	SDL_mutex *mut; // mutex para proteger la lista de movimientos
	std::map<int,Movimiento*> movimientosDeCompetidores;

	void notificarMovimiento(int id, int tipo, int x, int y);
};

#endif //_JUEGO_H_

