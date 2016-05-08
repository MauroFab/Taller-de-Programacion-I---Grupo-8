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

void Mapa::inicializar(SDL_Renderer* rendererRecibido) {

	ConfiguracionJuegoXML* configJuego = ConfiguracionJuegoXML::getInstance();

	tamanioMaximoMapa = configJuego->getTamanioMaximoFondo();
	renderer = rendererRecibido;

	texturaMapa= new Textura();
	if( !texturaMapa->cargarDeArchivo( configJuego->getPathFondo(),renderer ) ){
		texturaMapa->cargarDeArchivo( "fondoDefault.bmp",renderer );
	}

	texturaCarrier= new Textura();
	if( !texturaCarrier->cargarDeArchivo( configJuego->getPathCarrier(),renderer) ){
		texturaCarrier->cargarDeArchivo( "carrier.bmp",renderer );
	}
	texturaIsla= new Textura();
	if( !texturaIsla->cargarDeArchivo( configJuego->getPathIsla(),renderer) ){
		texturaIsla->cargarDeArchivo( "signoInterrogacion.bmp",renderer );
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
	delete texturaCarrier;
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

void Mapa::crearCarrierEn(int x, int y){

	ElementoDelMapa* elementoDelMapa;
	elementoDelMapa = new ElementoDelMapa(x,y, renderer,texturaCarrier);
	elementosDelMapa.push_back(elementoDelMapa);
}