#include "Graficador.h"

bool Graficador::instanceFlag = false;
Graficador* Graficador::instance = NULL;


Graficador* Graficador::getInstance() {
	
	if(!instanceFlag){
        instance = new Graficador();
        instanceFlag = true;
    }
    return instance;
}

Graficador::Graficador(void) {
}

Graficador::~Graficador(void) {
	
	std::map<int, GraficoAvion*>::iterator it;
	
	for (it = graficosAvion.begin(); it != graficosAvion.end(); it++) {
		delete ((*it).second);
	}

	delete graficoProyectil;
}

void Graficador::inicializar(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void Graficador::cargarDatosAvion(int id, std::string pathAvion, int cantFotogramas, int ancho, int alto) {

	GraficoAvion* grafico = new GraficoAvion(renderer, id, pathAvion, cantFotogramas, ancho, alto);
	graficosAvion.insert(std::pair<int, GraficoAvion*>(id, grafico));
	printf("1");
}

void Graficador::cargarDatosProyectil(std::string pathProyectil, int cantFotogramas, int ancho, int alto) {

	graficoProyectil = new GraficoProyectil(renderer, pathProyectil, cantFotogramas, ancho, alto);
}

void Graficador::graficarAviones(std::list<EstadoAvion*> listaAviones) {

	std::list<EstadoAvion*>::iterator it;

	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {

		GraficoAvion* grafico = graficosAvion.at((*it)->getId());

		SDL_Rect* clip = grafico->getCurrentClip((*it)->getFrame());

		Textura* textura = grafico->getTextura();

		textura->render((*it)->getPosX(), (*it)->getPosY(), renderer, clip);
	}
	//printf("2");
}

void Graficador::graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles) {

	std::list<EstadoProyectil*>::iterator it;

	for (it = listaProyectiles.begin(); it != listaProyectiles.end(); it++) {

		SDL_Rect* clip = graficoProyectil->getCurrentClip((*it)->getFrame());

		Textura* textura = graficoProyectil->getTextura();

		textura->render((*it)->getPosX(), (*it)->getPosY(), renderer, clip);
	}
}