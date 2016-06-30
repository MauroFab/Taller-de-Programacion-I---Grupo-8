#include "Juego.h"

Juego::Juego()
{
	JuegoContainer * cont = JuegoContainer::getInstance();
	cont->setGameData(this,0,0);
	this->_state = NULL;
	this->_paused = false;
}
Juego::Juego(int p_width, int p_height, NivelEstado* arg3)
{
	JuegoContainer * cont = JuegoContainer::getInstance();
	cont->setGameData(this,p_width,p_height);
	this->_state = arg3;
	this->_paused = false;
}

Juego::~Juego()
{
}
void Juego::run(){
	bool b_run = true;
	inicializar();
	while (b_run){
		handleEvents();
		update();
		render();
	}
	clean();	
}
void Juego::inicializar(){
	
}

void Juego::clean(){
	
}

void Juego::handleEvents(){
	
}

void Juego::switchState(NivelEstado * nivel)
{
	if (this->_state != NULL) {
		this->_state->destroy();
	}
    this->_state = nivel;
    this->_state->create();
}

void Juego::update(){
	cout <<"Juego::update()" <<endl;
    if (this->_paused)
    {
//                this->pause.update();
    }
    else
    {
        this->_state->update();
    }
    this->_state->preProcess();
    this->_state->render();
    this->_state->postProcess();
    return;
}

void Juego::render(){
	
}
