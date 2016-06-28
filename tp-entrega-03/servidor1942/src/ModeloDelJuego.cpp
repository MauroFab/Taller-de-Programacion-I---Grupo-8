#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios){
	this->cantidadMaximaDeUsuarios = cantidadMaximaDeUsuarios;
	crearAviones(servidorXml);
	setPosicionInicialListAvion();
	this->mapa = new Mapa(servidorXml);
	// Crea un temporizador con 10 segundos
	this->temporizadorEtapa = new Temporizador(10);
	//A partir de acá es una carga media manual de aviones enemigos
	//Primero armo una formacion
	 int cantidadDeAvionesDeLaFormacion = 4;
	 int posicionEnElMapa = 800;
	 int posicionPantallaSalida = 500;
	 //La formacion crea automaticamente todo los aviones, en un futuro servira para validar la destruccion completa de la misma
	 FakeFormacionDeEnemigos formacion(cantidadDeAvionesDeLaFormacion,posicionPantallaSalida,posicionEnElMapa);

	 //Agrego la formacion a la lista de formaciones, que se usa para chequear los bonus de puntos
	 formaciones.push_front(formacion);

	 //Luego los agrego a los avionesEnemigos del juego, poniendo la lista de aviones de la formacion en la de enemigos del juego
	 std::list<FakeAvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
	 avionesEnemigos.insert(avionesEnemigos.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());

	 //Creo un avion mediano, 300 y 800 son las coordenadas iniciales
	 avionesEnemigos.push_back(new FakeAvionMiddle(300,800));
	 //Y otro
	 avionesEnemigos.push_back(new FakeAvionMiddle(200,1000));
	  //Y otro
	 avionesEnemigos.push_back(new FakeAvionMiddle(100,1200));
	 //Lo mismo para el grande
	 avionesEnemigos.push_back(new FakeAvionBig(300,800));

	 //Creo power ups
	 powerUps.push_back(PowerUp(10,1000,500, TIPO_PUNTOS));
	 powerUps.push_back(PowerUp(100,800,500, TIPO_MUERTE));
	 powerUps.push_back(PowerUp(200,600,500, TIPO_PUNTOS));
	 powerUps.push_back(PowerUp(300,400,500, TIPO_AMETRALLADORA));
}

ModeloDelJuego::~ModeloDelJuego(){
	delete this->avionEnemigoBeta;
	delete this->mapa;
	delete this->temporizadorEtapa;
}

void ModeloDelJuego::crearAviones(ServidorXml* servidorXml){
	this->listAvion = new Avion*;
	AvionXml** avionXml;
	avionXml = servidorXml->getListaAviones();
	avionXml = servidorXml->getListaAviones();
	SpriteXml** spriteXml;
	spriteXml = servidorXml->getListaSprites();

	int anchoDeLaVentana, altoDeLaVentana;
	anchoDeLaVentana = servidorXml->getVentanaXmlCopy()->getAncho();
	altoDeLaVentana = servidorXml->getVentanaXmlCopy()->getAlto();

	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		SpriteXml* spriteBala;
		BalaView* balaView;
		BalaModel* balaModel;
		//Todo lo relacionado a la bala se saca del avion 0
		//No se usa uno solo para poder liberar la memoria por separado al eliminar el avion
		spriteBala = SpriteXml::findSpriteById(avionXml[0]->getIdSpBala(),spriteXml,servidorXml->getCanSprs());
		balaModel = new BalaModel(avionXml[0]);
		balaView = new BalaView(balaModel, spriteBala);
		AvionView* avionView;
		AvionModel* avionModel;
		SpriteXml* spriteAvion;
		spriteAvion = SpriteXml::findSpriteById(avionXml[i]->getIdSpAvion(),spriteXml,servidorXml->getCanSprs());
		avionModel = new AvionModel(avionXml[i]);
		avionView = new AvionView(avionModel, spriteAvion);
		this->listAvion[i] = new Avion(anchoDeLaVentana, altoDeLaVentana, avionView, balaView);
	}
	//---------agregado para TEST de movimiento
	UtilJuego * utilJ = UtilJuego::getInstance();
	int pos_x = utilJ->calcRandom(100,400);
	int pos_y = utilJ->calcRandom(900,1000);
	this->avionEnemigoBeta = new AvionEnemigo(pos_x,pos_y);
}

void ModeloDelJuego::actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento){
	this->listAvion[idDelJugadorQueMandoElEvento]->realizarAccionEnBaseA(evento);
}

// La posición (0,0) es en la esquina inferior izquierda
void ModeloDelJuego::setPosicionInicialListAvion(){
	Posicion posicionInicialParaTodos = Posicion(200,50);
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		this->listAvion[i]->setPosicion(posicionInicialParaTodos);
	}

}

list<SuperficieOcupada> ModeloDelJuego::getSuperficiesOcupadasPorJugadores(){
	list<SuperficieOcupada> superficies;
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		superficies.push_back(this->listAvion[i]->getSuperficieOcupada());
	}
	return superficies;
}

void ModeloDelJuego::actualizarMovimientos(){

	// Mientras se este en una determinada etapa
	if (!this->mapa->seTerminoEtapa()) {

		this->mapa->actualizar();

		for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
			this->listAvion[i]->mover(avionesEnemigos, powerUps);
		}
	
		std::list<EstadoPowerUp> estadoPowerUps;
		std::list<PowerUp>::iterator itP;
		for (itP = powerUps.begin(); itP != powerUps.end(); itP++) {
			(*itP).continuarMovimiento();
		}

		list<FakeAvionEnemigo*>::iterator it;
		list<SuperficieOcupada> superficies = getSuperficiesOcupadasPorJugadores();
		for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
			(*it)->continuarMovimiento(superficies);
		}

		//Luego de todos los movimientos, chequeo si tengo que bonificar a alguien por destruir
		//una formacion
		list<FakeFormacionDeEnemigos>::iterator itF;
		for (itF = formaciones.begin(); itF != formaciones.end(); itF++) {
			//Si esa formacion fue destruida por un mismo avion
			//Y nunca entrego puntos
			if((*itF).todosLosAvionesFueronDestruidosPorUnMismoAvion() && !(*itF).getEntreguePuntos()){
				(*itF).entregarPuntosAlJugadorQueDestruyoLaFormacion(listAvion);
			}
		}
	}
	else {
		// Ahora empieza a mostrarse la informacion durante al menos 10 segundos
		if (this->temporizadorEtapa->pasoElTiempoEstablecido()){
			this->mapa->avanzarEtapa();
			this->temporizadorEtapa->resetear();
		} else {
			this->temporizadorEtapa->avanzarTiempo();
		}
	}

	/*
	//---------
	int pixPasaron = this->mapa->getEstado()->getCantidadDePixeles();
	int height_ventana = this->mapa->altoVentana;
	int pos_y_real = height_ventana + pixPasaron;
//	printf("\npixPasaron=%d,height_ventana=%d",pixPasaron,height_ventana);
	//indicar si debe graficar o no
	if (this->avionEnemigoBeta != NULL){
		int y_avion = this->avionEnemigoBeta->y;
		int x_avion = this->avionEnemigoBeta->x;
		if (pos_y_real >= y_avion && !this->avionEnemigoBeta->getVisible()){
			this->avionEnemigoBeta->setVisible(true);
			avionesEnemigos.push_back(FakeAvionEnemigo(x_avion,500,68,120,2));
		}
		//una vez que se vuelve visible se puede mover
		if (this->avionEnemigoBeta->getVisible()){
			y_avion += this->avionEnemigoBeta->velocity.y;
			this->avionEnemigoBeta->y = y_avion;
//			printf("\ny_avion=%d",y_avion);
			list<FakeAvionEnemigo>::iterator it;
			int i = 0;
			for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
				if (i == 1)
					(*it).continuarMovimiento();
				i++;
			}
		}
	}*/
	///---------
}

EstadoAvion* ModeloDelJuego::getEstadoAvionJugador(int idAvion){
	return this->listAvion[idAvion]->getEstado();
}

EstadoJuego* ModeloDelJuego::obtenerEstadoDelJuego(){
	//Agrego los aviones de los jugadores
	std::list<EstadoAvion*> estadoDeAviones;
	std::list<EstadoJugador> estadoJugadores;
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		estadoDeAviones.push_back(this->listAvion[i]->getEstado());
		EstadoJugador estadoJugador = this->listAvion[i]->getEstadoJugadorAsociado();
		estadoJugadores.push_back(estadoJugador);
	}

	//Agrego los avionesEnemigos
	std::list<FakeAvionEnemigo*>::iterator it;
	for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
		estadoDeAviones.push_back((*it)->getEstado());
	}

	//Agrego los powerUps
	std::list<EstadoPowerUp> estadoPowerUps;
	std::list<PowerUp>::iterator itP;
	for (itP = powerUps.begin(); itP != powerUps.end(); itP++) {
		estadoPowerUps.push_back((*itP).getEstado());
	}

	EstadoMapa* estadoMapa = this->mapa->getEstado();

	EstadoJuego* estadoJuego = new EstadoJuego(estadoDeAviones, estadoJugadores, estadoPowerUps,
												estadoMapa);

	return estadoJuego;
}