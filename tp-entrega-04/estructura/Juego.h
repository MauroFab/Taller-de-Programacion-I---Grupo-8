#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <iostream>
#include "ObjetoItem.h"
#include "NivelEstado.h"
#include "JuegoContainer.h"
using namespace std;

class Juego
{
public:
    NivelEstado*  _state;
    bool _paused;
public:
	Juego();
	Juego(int p_width, int p_height, NivelEstado* arg3);
	virtual ~Juego();
	void run();
	void inicializar();
	void clean();
	void handleEvents();
	void switchState(NivelEstado * nivel);
	void update();
	void render();
	
};

#endif //_JUEGO_H_
