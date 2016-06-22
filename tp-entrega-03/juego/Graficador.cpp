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
Graficador::Graficador() {
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
void Graficador::graficarAviones(std::list<EstadoAvion*> listaAviones, int idDelJugador) {
	std::list<EstadoAvion*>::iterator it;
	EstadoAvion* estadoDelAvionDeEsteCliente;
	//Grafico todos los aviones y sus proyectiles, menos el de este cliente
	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {
		if((*it)->getId() != idDelJugador){
			GraficoAvion* grafico = mapaGraficosAvion.at((*it)->getId());
			SDL_Rect* clip = grafico->getCurrentClip((*it)->getFrame());
			Textura* textura = grafico->getTextura();
			textura->render((*it)->getPosX(), this->ventanaAlto - (*it)->getPosY() - textura->getHeight(), renderer, clip);
			this->graficarProyectiles((*it)->getEstadosProyectiles());
		}else{
			estadoDelAvionDeEsteCliente = (*it);
		}
	}
	//El avion del jugador del cliente debe ser graficado ultimo para que siempre se vea por encima
	GraficoAvion* grafico = mapaGraficosAvion.at(idDelJugador);
	SDL_Rect* clip = grafico->getCurrentClip(estadoDelAvionDeEsteCliente->getFrame());
	Textura* textura = grafico->getTextura();
	textura->render(estadoDelAvionDeEsteCliente->getPosX(), this->ventanaAlto - estadoDelAvionDeEsteCliente->getPosY() - textura->getHeight(), renderer, clip);
	this->graficarProyectiles(estadoDelAvionDeEsteCliente->getEstadosProyectiles());

	//grafica los puntos de vida del avion del jugador
	int intPuntosDeVida = estadoDelAvionDeEsteCliente->getPuntosDeVida();
	string strVida = static_cast<ostringstream*>( &(ostringstream() << intPuntosDeVida) )->str();
	string strEtiquetaVida("Vidas: ");
	strEtiquetaVida.append(strVida);
 	Etiqueta etiqueta(renderer,TTF_OpenFont("sfd/FreeSans.ttf", 24), strEtiquetaVida); 
	etiqueta.setPosicion(0,600);
	etiqueta.render();
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

void Graficador::graficarJuego(EstadoJuego* estadoJuego, int idDelJugador){
	actualizarMapa(estadoJuego->getEstadoDelMapa());
	graficarMapa();	
	graficarAviones(estadoJuego->getEstadoDeLosAviones(), idDelJugador);
	int puntajeServidor = 0;
	Graficador::getInstance()->graficarPuntaje(puntajeServidor);
}