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
	for (it = mapaGraficosAvion.begin(); it != mapaGraficosAvion.end(); it++) {
		delete ((*it).second);
	}
	delete graficoProyectil;
}
void Graficador::inicializar(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
void Graficador::agregarDatosAvion(AvionView * avionView) {
	GraficoAvion* grafico = new GraficoAvion(renderer, avionView);
	mapaGraficosAvion.insert(std::pair<int, GraficoAvion*>(avionView->avionModel->id, grafico));
}
void Graficador::agregarDatosBala(BalaView * balaView) {
	graficoProyectil = new GraficoProyectil(renderer,balaView);
}
void Graficador::graficarAviones(std::map<int,EstadoAvion*> listaAviones) {
	std::map<int, EstadoAvion*>::iterator it;
	//TODO error en disen..
	//BUG-000 Cada tanto el mensaje llega incompleto, con basura, y crashea acá.
	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {
		GraficoAvion* grafico = mapaGraficosAvion.at(it->second->getId());
		SDL_Rect* clip = grafico->getCurrentClip(it->second->getFrame());
		Textura* textura = grafico->getTextura();
		textura->render(it->second->getPosX(), it->second->getPosY(), renderer, clip);
		this->graficarProyectiles(it->second->getEstadosProyectiles());
	}
}
void Graficador::graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles) {
	std::list<EstadoProyectil*>::iterator it;
	for (it = listaProyectiles.begin(); it != listaProyectiles.end(); it++) {
		SDL_Rect* clip = graficoProyectil->getCurrentClip((*it)->getFrame());
		Textura* textura = graficoProyectil->getTextura();
		textura->render((*it)->getPosX(), (*it)->getPosY(), renderer, clip);
	}
}

void Graficador::graficarAvionesAll() {
	std::map<int, GraficoAvion*>::iterator it;
	int x = 10;
	int y = 15;
	for (it = mapaGraficosAvion.begin(); it != mapaGraficosAvion.end(); it++) {
		GraficoAvion* grafico = (*it).second;
		EstadoAvion tempEstadoAvion(-1,0,x,y);
		SDL_Rect* clip = grafico->getCurrentClip(tempEstadoAvion.getFrame());
		Textura* textura = grafico->getTextura();
		textura->render(tempEstadoAvion.getPosX(), tempEstadoAvion.getPosY(), renderer, clip);
		x += 50;
		y += 50;		
	}	
}
