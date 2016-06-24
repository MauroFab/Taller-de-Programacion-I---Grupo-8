#include "JuegoContainer.h"

JuegoContainer * JuegoContainer::instance = NULL;

JuegoContainer* JuegoContainer::getInstance() {
	if(instance == NULL){
        instance = new JuegoContainer();
    }
    return instance;
}

JuegoContainer::JuegoContainer()
{
	this->_game = NULL;
}

JuegoContainer::~JuegoContainer()
{
}

void JuegoContainer::set_state(NivelEstado * arg1) {
	_game->switchState(arg1);
	return;
}

void JuegoContainer::setGameData(Juego * juego, int p_width, int p_height) {
	_game = juego;
	width = p_width;
	height = p_height;
//	scroll = NULL;
//	unfollow();
//	levels = new Vector();
//	scores = new Vector();
	level = 0;
	score = 0;
//	timeScale = 1;
	elapsed = 0.1333333;
}
