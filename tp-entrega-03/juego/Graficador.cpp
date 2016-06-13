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
void Graficador::inicializar(SDL_Renderer* renderer, int ventanaAncho, int ventanaAlto) {
	this->renderer = renderer;
	this->ventanaAncho = ventanaAncho;
	this->ventanaAlto = ventanaAlto;
}
void Graficador::agregarDatosAviones(AvionView* *listaAvionView, int canAvionV) {
	for(int v = 0; v < canAvionV; v++){
		AvionView * avionV = listaAvionView[v];
		GraficoAvion* grafico = new GraficoAvion(renderer, avionV);
		mapaGraficosAvion.insert(std::pair<int, GraficoAvion*>(avionV->avionModel->id, grafico));
	}
}
void Graficador::agregarDatosBala(BalaView * balaView) {
	graficoProyectil = new GraficoProyectil(renderer,balaView);
}
void Graficador::graficarAviones(std::map<int,EstadoAvion*> listaAviones) {
	std::map<int, EstadoAvion*>::iterator it;
	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {
		GraficoAvion* grafico = mapaGraficosAvion.at(it->second->getId());
		SDL_Rect* clip = grafico->getCurrentClip(it->second->getFrame());
		Textura* textura = grafico->getTextura();
		textura->render(it->second->getPosX(), this->ventanaAlto - it->second->getPosY() - textura->getHeight(), renderer, clip);
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