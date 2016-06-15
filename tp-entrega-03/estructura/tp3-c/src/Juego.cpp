#include "Juego.h"

Juego::Juego()
{
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

void Juego::update(){
	
}

void Juego::render(){
	
}
