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
	for (int i = 0;i < MAX_CANTIDAD_ESCENARIOS; i++){
		this->graficosMapa[i] = NULL;
	}
	
}

Graficador::~Graficador(void) {
	std::map<int, GraficoAvion*>::iterator it;
	for (it = mapaGraficosAvion.begin(); it != mapaGraficosAvion.end(); it++) {
		delete ((*it).second);
	}
	delete graficoProyectilMejorado;
	for (int i = 0;i < MAX_CANTIDAD_ESCENARIOS; i++){
		if (this->graficosMapa[i] != NULL)
			delete this->graficosMapa[i];
	}
	delete graficoMapa;
	delete graficoPuntaje;
	delete graficoPuntosVida;
	delete graficadorPowerUp;
	delete graficadorInformacion;
	delete vistaExplosion;
}

void Graficador::inicializar(SDL_Renderer* renderer, int ventanaAncho, int ventanaAlto) {
	this->renderer = renderer;
	this->ventanaAncho = ventanaAncho;
	this->ventanaAlto = ventanaAlto;
	this->graficoPuntaje = new GraficadorPuntaje(renderer);
	this->graficoPuntosVida = new GraficadorPuntosVida(renderer);
	this->graficadorPowerUp = new GraficadorPowerUp(renderer);
	this->graficadorInformacion = new GraficadorInformacion(renderer);
	this->vistaExplosion = new VistaExplosion(renderer);
	this->vistaFinalJuego = new FondoInicio(PATH_FINAL_JUEGO, renderer);
}

void Graficador::agregarDatosAviones(AvionView* *listaAvionView, int canAvionV) {
	for(int v = 0; v < canAvionV; v++){
		AvionView * avionV = listaAvionView[v];
		GraficoAvion* grafico = new GraficoAvion(renderer, avionV);
		mapaGraficosAvion.insert(std::pair<int, GraficoAvion*>(avionV->avionModel->id, grafico));
	}
}

void Graficador::agregarDatosBala(BalaView * balaView) {
	graficoProyectilMejorado = new GraficoProyectil(renderer,balaView);

	//Harcodeo la bala comun
	texturaProyectilSinMejora = new Textura();
	char path[200]= "../cliente1942/disparo_1.bmp";
	texturaProyectilSinMejora->cargarDeArchivo(path,renderer);
}

void Graficador::agregarDatosMapa(EscenarioView ** listaEscenariosView, int canEscenariosV, int posicionInicial) {
	
	for (int i = 0; i < canEscenariosV; i++) {
		GraficoMapa* graficoMapa = new GraficoMapa(renderer, listaEscenariosView[i]->getFondoView(), posicionInicial);
		graficoMapa->crearElementos(listaEscenariosView[i]->getElementosView(), listaEscenariosView[i]->getCanElemV());
		graficosMapa[i] = graficoMapa;
	}
	this->graficoMapa = graficosMapa[0];
}

bool Graficador::estaDestruidoElAvion(EstadoAvion* estadoAvion){
	return (estadoAvion->getPuntosDeVida() <= 0);
}

EstadoAvion* Graficador::obtengoElEstadoAvionDelClienteYGraficoLosDemasAviones
							(std::list<EstadoAvion*> listaAviones, int idDelJugador){
	std::list<EstadoAvion*>::iterator it;
	EstadoAvion* estadoDelAvionDeEsteCliente;
	for (it = listaAviones.begin(); it != listaAviones.end(); it++) {
		if((*it)->getId() != idDelJugador ){
			if(!estaDestruidoElAvion(*it)){
				GraficoAvion* grafico = mapaGraficosAvion.at((*it)->getId());
				SDL_Rect* clip = grafico->getCurrentClip((*it)->getFrame());
				Textura* textura = grafico->getTextura();
				textura->render((*it)->getPosX(), this->ventanaAlto - (*it)->getPosY() - textura->getHeight(), renderer, clip);
			}else{
				vistaExplosion->procesarEstadoAvionQueEstaDestruido((*it));
			}
			this->graficarProyectiles((*it)->getEstadosProyectiles());
		}else{
			estadoDelAvionDeEsteCliente = (*it);
		}
	}
	return estadoDelAvionDeEsteCliente;
}

void Graficador::graficoElAvionDelCliente(EstadoAvion* estadoDelAvionDeEsteCliente){
	if(!estaDestruidoElAvion(estadoDelAvionDeEsteCliente)){
		//El avion del jugador del cliente debe ser graficado ultimo para que siempre se vea por encima
		GraficoAvion* grafico = mapaGraficosAvion.at(estadoDelAvionDeEsteCliente->getId());
		SDL_Rect* clip = grafico->getCurrentClip(estadoDelAvionDeEsteCliente->getFrame());
		Textura* textura = grafico->getTextura();
		textura->render(estadoDelAvionDeEsteCliente->getPosX(), this->ventanaAlto - estadoDelAvionDeEsteCliente->getPosY() - textura->getHeight(), renderer, clip);
		this->graficarProyectiles(estadoDelAvionDeEsteCliente->getEstadosProyectiles());
	}else{
		vistaExplosion->procesarEstadoAvionQueEstaDestruido(estadoDelAvionDeEsteCliente);
	}
}

void Graficador::graficoLosPuntosDeVidaDelAvionDeEsteCliente(EstadoAvion* estadoDelAvionDeEsteCliente){
	int puntosDeVida = estadoDelAvionDeEsteCliente->getPuntosDeVida();
	graficoPuntosVida->renderizarPuntosDeVida(puntosDeVida);
}

void Graficador::graficarAviones(std::list<EstadoAvion*> listaAviones, int idDelJugador) {
	
	//Grafico todos los aviones y sus proyectiles, menos el de este cliente
	EstadoAvion* estadoDelAvionDeEsteCliente;
	estadoDelAvionDeEsteCliente =
		obtengoElEstadoAvionDelClienteYGraficoLosDemasAviones(listaAviones, idDelJugador);
	//Siempre el avion del cliente propio se grafica al final, asi se ve por encima de los demas
	graficoElAvionDelCliente(estadoDelAvionDeEsteCliente);
	graficoLosPuntosDeVidaDelAvionDeEsteCliente(estadoDelAvionDeEsteCliente);
}

void Graficador::graficoProyectilConLaTexturaHardcodeada(EstadoProyectil* estadoProyectil){
	int x = estadoProyectil->getPosX();
	int y = estadoProyectil->getPosY();
	this->texturaProyectilSinMejora->render(x,640 - y,renderer);
}

void Graficador::graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles) {
	std::list<EstadoProyectil*>::iterator it;
	for (it = listaProyectiles.begin(); it != listaProyectiles.end(); it++) {
		if((*it)->getVisible()){
			if((*it)->getMejorado()){
 				SDL_Rect* clip = graficoProyectilMejorado->getCurrentClip((*it)->getFrame());
				Textura* textura = graficoProyectilMejorado->getTextura();
				textura->render((*it)->getPosX(), 640 - (*it)->getPosY(), renderer, clip);
			}else{
				graficoProyectilConLaTexturaHardcodeada((*it));
			}
		}
	}
}

void Graficador::graficarMapa() {
	graficoMapa->graficarFondoYElementos();
}

void Graficador::graficarPuntaje(int puntaje) {
	graficoPuntaje->renderizarPuntaje(puntaje);
}

void Graficador::reiniciar() {
	vistaExplosion->reiniciar();
	graficoMapa->reiniciar();
}

void Graficador::actualizarMapa(EstadoMapa* estadoMapa) {
	
	this->graficoMapa = this->graficosMapa[estadoMapa->getIdEtapa()];
	if (this->graficoMapa != NULL){
		this->graficoMapa->actualizar(estadoMapa);
	}
}

void Graficador::mostrarInformacion(std::list<EstadoJugador> estadosJugadores) {

	int numeroDeEquipo = estadosJugadores.front().getEquipo();
	int cantidadJugadores = estadosJugadores.size();

	this->graficadorInformacion->seleccionarVista(numeroDeEquipo, cantidadJugadores);
	this->graficadorInformacion->render(estadosJugadores);
}

int Graficador::buscarPuntajeDelJugadorEn(EstadoJuego* estadoJuego, int id){
	std::list<EstadoJugador>::iterator it;
	std::list<EstadoJugador> listaDeEstados;
	listaDeEstados = estadoJuego->getEstadoDeLosJugadores();
	for(it = listaDeEstados.begin();  it != listaDeEstados.end(); it++){
		int idDelEstadoRevisado;
		idDelEstadoRevisado = (*it).getid();
		//No quiero armar un while para buscar a mano, ni recorrer toda la lista
		//Si ya lo encontre
		if(idDelEstadoRevisado == id){
			break;
		}
	}
	return(*it).getPuntajeAcumulado();
}

void Graficador::graficarJuego(EstadoJuego* estadoJuego, int idDelJugador){
	
	if (estadoJuego->getEstadoDelMapa()->getCodigoReinicio() == JUEGO_FINALIZADO) {
		graficarFinalJuego();
	} else {
		if (estadoJuego->getEstadoDelMapa()->hayQueMostrarInformacion()) {
			mostrarInformacion(estadoJuego->getEstadoDeLosJugadores());
		} else {
			actualizarMapa(estadoJuego->getEstadoDelMapa());
			graficarMapa();	
			graficarAviones(estadoJuego->getEstadoDeLosAviones(), idDelJugador);
			int puntajeDelJugador = buscarPuntajeDelJugadorEn(estadoJuego, idDelJugador);
			Graficador::getInstance()->graficarPuntaje(puntajeDelJugador);
			this->graficadorPowerUp->graficarPowerUps(estadoJuego->getEstadoPowerUps());
		}
	}
}

void Graficador::graficarFinalJuego() {
	this->vistaFinalJuego->render();
}