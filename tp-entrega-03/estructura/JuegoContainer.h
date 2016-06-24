#ifndef _JUEGOCONTAINER_H_
#define _JUEGOCONTAINER_H_

#include <iostream>
#include "Juego.h"
#include "NivelEstado.h"
using namespace std;

class Juego;
class JuegoContainer
{
private:
	static JuegoContainer* instance;
	JuegoContainer();
public:
	Juego * _game;
	double elapsed;
	int width;
	int height;
	int level;
	int score;
public:
	~JuegoContainer();
	static JuegoContainer* getInstance();
	int get_GAME_WIDTH() {
		return 800;
	}

	int get_GAME_HEIGHT() {
		return 600;
	}
	void set_state(NivelEstado * arg1);
	void setGameData(Juego * juego, int p_width, int p_height);

};
#endif //_JUEGOCONTAINER_H_
