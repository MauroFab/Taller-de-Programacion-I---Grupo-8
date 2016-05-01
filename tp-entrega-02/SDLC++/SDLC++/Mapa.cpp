#include "Mapa.h"


Mapa::Mapa(SDL_Renderer* rendererRecibido, Textura* texturaMapaRecibida, Textura* texturaIslaRecibida){
	texturaMapa = texturaMapaRecibida;
	texturaIsla = texturaIslaRecibida;
	anchoMapa = texturaMapaRecibida->getWidth();
	altoMapa = texturaMapaRecibida->getHeight();
	pixelesAvanzados = 0;
	scrollingOffset = 0;
	renderer = rendererRecibido;
	elementoDelMapa = NULL;
	cantidadDePixelesQuePasaron = 0;
}


Mapa::~Mapa(){

}


void Mapa::graficar(){
	//Después de la ultima posicion de la imagen de fondo sigue la primera
	if(scrollingOffset >= altoMapa)
		scrollingOffset = 0;
	texturaMapa->render(0, scrollingOffset, renderer);
	texturaMapa->render(0, scrollingOffset - altoMapa, renderer);
	if(elementoDelMapa != NULL)
		elementoDelMapa->graficarseSiEstaEnPantalla(altoMapa + cantidadDePixelesQuePasaron, 
													cantidadDePixelesQuePasaron);
	scrollingOffset++;
	cantidadDePixelesQuePasaron++;
}


void Mapa::crearIslaEn(int x, int y){
	elementoDelMapa = new ElementoDelMapa(x,y, renderer,texturaIsla);
}
