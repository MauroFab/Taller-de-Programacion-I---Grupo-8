#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "Constantes.h"

class Juego{

public:

	static Juego* getInstance();
	~Juego();

	void close();
	void ejecutar();
	void cargarConfiguracion();
	//void agregarNuevoEstadoAvion();

private:

	static bool instanceFlag;
	static Juego* instance;
	Juego();
	bool init();
	
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	//std::list<EstadoAvion*> aviones;

};

#endif //_JUEGO_H_

