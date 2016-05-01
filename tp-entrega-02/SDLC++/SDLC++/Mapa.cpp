#include "Mapa.h"


Mapa::Mapa(SDL_Renderer* rendererRecibido, Textura* texturaMapaRecibida, Textura* texturaIslaRecibida){
	texturaMapa = texturaMapaRecibida;
	texturaIsla = texturaIslaRecibida;
	anchoMapa = texturaMapaRecibida->getWidth();
	altoMapa = texturaMapaRecibida->getHeight();
	pixelesAvanzados = 0;
	scrollingOffset = 0;
	renderer = rendererRecibido;
	cantidadDePixelesQuePasaron = 0;
}


Mapa::~Mapa(){
	std::list<ElementoDelMapa*>::iterator it;

for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
     delete (*it);
}

void Mapa::graficarElementosDelMapa(){

std::list<ElementoDelMapa*>::iterator it;

for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
     (*it)->graficarseSiEstaEnPantalla(altoMapa + cantidadDePixelesQuePasaron, cantidadDePixelesQuePasaron);
}

void Mapa::graficar(){
	//Después de la ultima posicion de la imagen de fondo sigue la primera
	if(scrollingOffset >= altoMapa)
		scrollingOffset = 0;
	texturaMapa->render(0, scrollingOffset, renderer);
	texturaMapa->render(0, scrollingOffset - altoMapa, renderer);
	graficarElementosDelMapa();
	scrollingOffset++;
	cantidadDePixelesQuePasaron++;
}


void Mapa::crearIslaEn(int x, int y){
	ElementoDelMapa* elementoDelMapa;
	elementoDelMapa = new ElementoDelMapa(x,y, renderer,texturaIsla);
	elementosDelMapa.push_back(elementoDelMapa);
}
