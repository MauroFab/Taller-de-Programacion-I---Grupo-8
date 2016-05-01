#include "Mapa.h"


Mapa::Mapa(SDL_Renderer* rendererRecibido, Textura* texturaMapaRecibida){
	texturaMapa = texturaMapaRecibida;
	anchoMapa = texturaMapaRecibida->getWidth();
	altoMapa = texturaMapaRecibida->getHeight();
	pixelesAvanzados = 0;
	scrollingOffset = 0;
	renderer = rendererRecibido;
}


Mapa::~Mapa(){

}


void Mapa::graficar(){
	//Después de la ultima posicion de la imagen de fondo sigue la primera
	if(scrollingOffset >= altoMapa)
		scrollingOffset = 0;
	texturaMapa->render(0, scrollingOffset, renderer);
	texturaMapa->render(0, scrollingOffset - altoMapa, renderer);
	scrollingOffset++;

}
