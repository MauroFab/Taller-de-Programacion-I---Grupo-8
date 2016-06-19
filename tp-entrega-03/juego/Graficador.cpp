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
	delete graficoMapa;
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

void Graficador::agregarDatosMapa(FondoView * fondoView, ElementoView* *listaElementosView, int canElemV, int posicionInicial) {
	graficoMapa = new GraficoMapa(renderer, fondoView, posicionInicial);
	graficoMapa->crearElementos(listaElementosView, canElemV);
}
void Graficador::graficarAviones(std::list<EstadoAvion*> listaAviones) {
	std::list<EstadoAvion*>::iterator it;
	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {
		GraficoAvion* grafico = mapaGraficosAvion.at((*it)->getId());
		SDL_Rect* clip = grafico->getCurrentClip((*it)->getFrame());
		Textura* textura = grafico->getTextura();
		textura->render((*it)->getPosX(), this->ventanaAlto - (*it)->getPosY() - textura->getHeight(), renderer, clip);
		this->graficarProyectiles((*it)->getEstadosProyectiles());
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
void Graficador::graficarMapa() {
	graficoMapa->graficarFondoYElementos();
}
void Graficador::graficarPuntaje(int puntaje) {
	GraficadorPuntaje graficador;
	graficador.renderizarPuntaje(renderer,puntaje);
}

void Graficador::reiniciarMapa() {
	graficoMapa->reiniciar();
}

void Graficador::actualizarMapa(EstadoMapa* estadoMapa) {
	graficoMapa->actualizar(estadoMapa);
}

void Graficador::graficarJuego(EstadoJuego* estadoJuego){
	actualizarMapa(estadoJuego->getEstadoDelMapa());
	graficarMapa();
	estadoJuego->getEstadoDeLosAviones();
	graficarAviones(estadoJuego->getEstadoDeLosAviones());
	int puntajeQueEnAlgunMomentoSeRecibiraDelServidor = 0;
	Graficador::getInstance()->graficarPuntaje(puntajeQueEnAlgunMomentoSeRecibiraDelServidor);
}