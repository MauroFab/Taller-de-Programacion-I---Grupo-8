#include "Mapa.h"

bool Mapa::instanceFlag = false;
Mapa* Mapa::instance = NULL;

Mapa* Mapa::getInstace() {

	if(!instanceFlag){
        instance = new Mapa();
        instanceFlag = true;
    }
    return instance;
}

void Mapa::inicializar(SDL_Renderer* rendererRecibido, std::string dirImagenMapa, std::string dirImagenIsla,
						int tamanioMaximoMapaRecibido) {
	tamanioMaximoMapa = tamanioMaximoMapaRecibido;
	bool success = true;
	renderer = rendererRecibido;
	texturaMapa= new Textura();
	if( !texturaMapa->cargarDeArchivo( dirImagenMapa,renderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	texturaIsla= new Textura();
	if( !texturaIsla->cargarDeArchivo( dirImagenIsla,renderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	anchoMapa = texturaMapa->getWidth();
	altoMapa = texturaMapa->getHeight();	
}

Mapa::Mapa(){
	
	pixelesAvanzados = 0;
	scrollingOffset = 0;
	cantidadDePixelesQuePasaron = 0;
}


Mapa::~Mapa(){
	std::list<ElementoDelMapa*>::iterator it;

	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
		 delete (*it);
	delete texturaIsla;
	delete texturaMapa;
}

void Mapa::graficarElementosDelMapa(){

std::list<ElementoDelMapa*>::iterator it;

for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
     (*it)->graficarseSiEstaEnPantalla(altoMapa + cantidadDePixelesQuePasaron, cantidadDePixelesQuePasaron);
}

void Mapa::graficar(){
	if(cantidadDePixelesQuePasaron > tamanioMaximoMapa)
		this->reiniciar();

	//Después de la ultima posicion de la imagen de fondo sigue la primera
	if(scrollingOffset >= altoMapa)
		scrollingOffset = 0;
	texturaMapa->render(0, scrollingOffset, renderer);
	texturaMapa->render(0, scrollingOffset - altoMapa, renderer);
	graficarElementosDelMapa();
	scrollingOffset++;
	cantidadDePixelesQuePasaron++;
}
void Mapa::reiniciar(){
	cantidadDePixelesQuePasaron = 0;
	scrollingOffset = 0;
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
		(*it)->reiniciar();
}
void Mapa::crearIslaEn(int x, int y){
	ElementoDelMapa* elementoDelMapa;
	elementoDelMapa = new ElementoDelMapa(x,y, renderer,texturaIsla);
	elementosDelMapa.push_back(elementoDelMapa);
}
