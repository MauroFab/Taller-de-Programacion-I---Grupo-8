#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios){
	this->cantidadMaximaDeUsuarios = usuarios->getCantidadMaximaDeUsuarios();
	crearAviones(servidorXml, usuarios);
	setPosicionInicialListAvion();
	this->servidorXml = servidorXml;
	this->mapa = new Mapa(this->servidorXml);
	// Crea un temporizador con 7 segundos
	this->temporizadorEtapa = new Temporizador(7);
	//A partir de acá es una carga media manual de aviones enemigos
	//Primero armo una formacion
	 int cantidadDeAvionesDeLaFormacion = 4;
	 int posicionEnElMapa = 800;
	 int posicionPantallaSalida = 500;
	 int cantidadMaximaDeNiveles = 10;
	 formacionesDeLosNiveles.resize(cantidadMaximaDeNiveles);
	 enemigosDeLosNiveles.resize(cantidadMaximaDeNiveles);
	 powerUpsDeLosNiveles.resize(cantidadMaximaDeNiveles);

	 for(int i = 0; i < servidorXml->getCanEsc(); i++){
		 preparoEliNivel(i, this->servidorXml);
	 }
	 if(servidorXml->getModo() == M_MODO_PRACTICA_COLABORACION || servidorXml->getModo() == M_MODO_PRACTICA_EQUIPO){
		 hacerInvulnerablesALosJugadores();
		 estoyEnModoPractica = true;
	 }else{
		 estoyEnModoPractica = false;
	 }
	 //preparoElPrimerNivel();
	 //preparoElSegundoNivel();
}

void ModeloDelJuego::hacerInvulnerablesALosJugadores(){
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		this->listAvion[i]->volverseInvulnerable();
	}
}

void ModeloDelJuego::hacerVulnerablesALosJugadores(){
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		this->listAvion[i]->dejarDeSerInvulnerable();
	}
}

void ModeloDelJuego::preparoEliNivel(int i, ServidorXml* servidorXml){
	std::list<FakeFormacionDeEnemigos> formacionesEnPreparacion;
	std::list<FakeAvionEnemigo*> avionesEnemigosEnPreparacion;
	std::list<PowerUp> powerUpsEnPreparacion;

	//Cargo aviones
	AvionEnemigoXml** enemigosXml = servidorXml->getListaEscenario()[i]->getListaEnemigos();
	for(int j = 0; j < servidorXml->getListaEscenario()[i]->getCanEnes(); j++){
		int x = enemigosXml[j]->getPosicion().coorX;
		int y = enemigosXml[j]->getPosicion().coorY;
		if(enemigosXml[j]->getTipo() ==  A_TIPO_BIG){
			avionesEnemigosEnPreparacion.push_back(new FakeAvionBig(x,y));
		}else if(enemigosXml[j]->getTipo() ==  A_TIPO_MIDDLE){
			avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(x,y));
		}else if(enemigosXml[j]->getTipo() ==  A_TIPO_FORMACION){
			//Salen de la posicion 500 de alto en el mapa. Son 10 aviones
			FakeFormacionDeEnemigos formacion(10,500,y);
			formacionesEnPreparacion.push_front(formacion);
			avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(300,800));
			std::list<FakeAvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
			avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());
		}else if(enemigosXml[j]->getTipo() ==  A_TIPO_MINI){
			avionesEnemigosEnPreparacion.push_back(new FakeAvionMini(x,y));
		}
	}
	
	PowerUpXml** powerUpXml = servidorXml->getListaEscenario()[i]->getListaPowerUp();
	//Cargo power ups
	for(int j = 0; j < servidorXml->getListaEscenario()[i]->getCanPows(); j++){
		int x = powerUpXml[j]->getPosicion().coorX;
		int y = powerUpXml[j]->getPosicion().coorY;
		if(powerUpXml[j]->getTipo() ==  P_TIPO_MUERTE){
			powerUpsEnPreparacion.push_back(PowerUp(x,y,0,TIPO_MUERTE));
		}else if(powerUpXml[j]->getTipo() ==  P_TIPO_AMETRALLADORA){
			powerUpsEnPreparacion.push_back(PowerUp(x,y,0,TIPO_AMETRALLADORA));
		}else if(powerUpXml[j]->getTipo() ==  P_TIPO_PUNTOS){
			powerUpsEnPreparacion.push_back(PowerUp(x,y,1000,TIPO_PUNTOS));
		}
	}

	 if(i == 0){
		 formaciones = formacionesEnPreparacion;
		 avionesEnemigos = avionesEnemigosEnPreparacion;
		 powerUps = powerUpsEnPreparacion;
	 }

	this->formacionesDeLosNiveles.at(i) = formacionesEnPreparacion;
	this->enemigosDeLosNiveles.at(i) = avionesEnemigosEnPreparacion;
	this->powerUpsDeLosNiveles.at(i) = powerUpsEnPreparacion;
}

void ModeloDelJuego::preparoElPrimerNivel(){

	 std::list<FakeFormacionDeEnemigos> formacionesEnPreparacion;
	 std::list<FakeAvionEnemigo*> avionesEnemigosEnPreparacion;
	 std::list<PowerUp> powerUpsEnPreparacion;

	 //A partir de acá es una carga media manual de aviones enemigos
	 //Primero armo una formacion
	 int cantidadDeAvionesDeLaFormacion = 4;
	 int posicionEnElMapa = 800;
	 int posicionPantallaSalida = 500;

	 //La formacion crea automaticamente todo los aviones, en un futuro servira para validar la destruccion completa de la misma
	 FakeFormacionDeEnemigos formacion(cantidadDeAvionesDeLaFormacion,posicionPantallaSalida,posicionEnElMapa);

	 //Agrego la formacion a la lista de formaciones, que se usa para chequear los bonus de puntos
	 formacionesEnPreparacion.push_front(formacion);
	  avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(300,800));
	 //Luego los agrego a los avionesEnemigos del juego, poniendo la lista de aviones de la formacion en la de enemigos del juego
	 std::list<FakeAvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
	 avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());

	 //Creo un avion mediano, 300 y 800 son las coordenadas iniciales
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(300,800));
	 //Y otro
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(200,1000));
	  //Y otro
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(100,1200));
	 //Lo mismo para el grande
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionBig(300,800));

	 //Creo power ups
	 powerUpsEnPreparacion.push_back(PowerUp(10,1000,500, TIPO_PUNTOS));
	 powerUpsEnPreparacion.push_back(PowerUp(100,800,500, TIPO_MUERTE));
	 powerUpsEnPreparacion.push_back(PowerUp(200,600,500, TIPO_PUNTOS));
	 powerUpsEnPreparacion.push_back(PowerUp(300,400,500, TIPO_AMETRALLADORA));

	 this->formacionesDeLosNiveles.at(0) = formacionesEnPreparacion;
	 this->enemigosDeLosNiveles.at(0) = avionesEnemigosEnPreparacion;
	 this->powerUpsDeLosNiveles.at(0) = powerUpsEnPreparacion;

	 formaciones = formacionesEnPreparacion;
	 avionesEnemigos = avionesEnemigosEnPreparacion;
	 powerUps = powerUpsEnPreparacion;
}

void ModeloDelJuego::preparoElSegundoNivel(){

	 std::list<FakeFormacionDeEnemigos> formacionesEnPreparacion;
	 std::list<FakeAvionEnemigo*> avionesEnemigosEnPreparacion;
	 std::list<PowerUp> powerUpsEnPreparacion;

	 //A partir de acá es una carga media manual de aviones enemigos
	 //Primero armo una formacion
	 int cantidadDeAvionesDeLaFormacion = 4;
	 int posicionEnElMapa = 800;
	 int posicionPantallaSalida = 500;

	 //La formacion crea automaticamente todo los aviones, en un futuro servira para validar la destruccion completa de la misma
	 FakeFormacionDeEnemigos formacion(cantidadDeAvionesDeLaFormacion,posicionPantallaSalida,posicionEnElMapa);

	 //Agrego la formacion a la lista de formaciones, que se usa para chequear los bonus de puntos
	 formacionesEnPreparacion.push_front(formacion);

	 //Luego los agrego a los avionesEnemigos del juego, poniendo la lista de aviones de la formacion en la de enemigos del juego
	 std::list<FakeAvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
	 avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());

	 //Creo un avion mediano, 300 y 800 son las coordenadas iniciales
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(300,800));
	 //Y otro
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(200,1000));
	  //Y otro
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionMiddle(100,1200));
	 //Lo mismo para el grande
	 avionesEnemigosEnPreparacion.push_back(new FakeAvionBig(300,800));

	 //Creo power ups
	 powerUpsEnPreparacion.push_back(PowerUp(10,1000,500, TIPO_PUNTOS));
	 powerUpsEnPreparacion.push_back(PowerUp(100,800,500, TIPO_MUERTE));
	 powerUpsEnPreparacion.push_back(PowerUp(200,600,500, TIPO_PUNTOS));
	 powerUpsEnPreparacion.push_back(PowerUp(300,400,500, TIPO_AMETRALLADORA));

	 this->formacionesDeLosNiveles.at(1) = formacionesEnPreparacion;
	 this->enemigosDeLosNiveles.at(1) = avionesEnemigosEnPreparacion;
	 this->powerUpsDeLosNiveles.at(1) = powerUpsEnPreparacion;
}

ModeloDelJuego::~ModeloDelJuego(){
	delete this->avionEnemigoBeta;
	delete this->mapa;
	delete this->temporizadorEtapa;
}

void ModeloDelJuego::crearAviones(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios){
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
		this->listAvion[i] = new Avion(anchoDeLaVentana, altoDeLaVentana, avionView, balaView, usuarios->getNombreDeUsuarioDeJugador(i));
	}
	//---------agregado para TEST de movimiento
	UtilJuego * utilJ = UtilJuego::getInstance();
	int pos_x = utilJ->calcRandom(100,400);
	int pos_y = utilJ->calcRandom(900,1000);
	this->avionEnemigoBeta = new AvionEnemigo(pos_x,pos_y);
}

void ModeloDelJuego::actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento){
	this->listAvion[idDelJugadorQueMandoElEvento]->realizarAccionEnBaseA(evento);
	if(evento->getNumeroDeEvento() == apretadaLaTeclaDeCambioDeModo){
		if(!estoyEnModoPractica){
			hacerInvulnerablesALosJugadores();
			estoyEnModoPractica = true;
		}else{
			hacerVulnerablesALosJugadores();
			estoyEnModoPractica = false;
		}
	} else if (evento->getNumeroDeEvento() == apretadaLaTeclaDeFinalizacionDePartida) {
		this->mapa->finalizarJuegoPorEvento();
	} else if (evento->getNumeroDeEvento() == apretadaLaTeclaDeReinicio) {
		this->mapa->reiniciar();
		for (int i = 0; i < cantidadMaximaDeUsuarios; i++) {
			this->listAvion[i]->reiniciar();
		}
		for(int i = 0; i < servidorXml->getCanEsc(); i++){
			preparoEliNivel(i, this->servidorXml);
		}
	}
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

bool ModeloDelJuego::hayDestruccionDeTodosLosAviones() {

	for (int i = 0; i < cantidadMaximaDeUsuarios; i++){
		if (!this->listAvion[i]->estoyDestruido()) return false;
	}
	return true;
}

void ModeloDelJuego::actualizarMovimientos(){

	// Mientras se este en una determinada etapa
	if (!this->mapa->seTerminoEtapa()) {

		this->mapa->actualizar();

		if (this->mapa->seEstaLLegandoAlFinalDeLaEtapa()) {
			for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
				Avion* avion = this->listAvion[i];
				Posicion* posicionI = new Posicion(avion->getSuperficieOcupada().obtenerPosicion().getPosX(), avion->getSuperficieOcupada().obtenerPosicion().getPosY());
				Posicion* posicionF = new Posicion(30 + i*80, 520);
				int velocidad = avion->getVelocidad();
				Movimiento* movimiento = new MovimientoAterrizaje(posicionI, posicionF, velocidad);
				avion->cambiarMovimiento(movimiento);
			}
		} else {
			for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
				Avion* avion = this->listAvion[i];
				avion->cambiarMovimiento(new MovimientoComun());
				if (this->mapa->empezoUnaNuevaEtapa()) {
					avion->setPosicion(Posicion(50, 240));
				}
			}
		}

		for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
			this->listAvion[i]->mover(avionesEnemigos, powerUps);
		}

		if (hayDestruccionDeTodosLosAviones()) {
			this->mapa->finalizarJuegoPorQueNoHayAviones();
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
		if (this->mapa->seTerminoEtapa() && !this->mapa->seTerminoJuego()) {
			// Ahora empieza a mostrarse la informacion durante al menos 10 segundos
			if (this->temporizadorEtapa->pasoElTiempoEstablecido()){
				this->mapa->avanzarEtapa();
				this->temporizadorEtapa->resetear();
				this->powerUps = this->powerUpsDeLosNiveles.at(mapa->idEtapaActual);
				this->avionesEnemigos = this->enemigosDeLosNiveles.at(mapa->idEtapaActual);
				this->powerUps = this->powerUpsDeLosNiveles.at(mapa->idEtapaActual);
			} else {
				this->temporizadorEtapa->avanzarTiempo();
			}
		} else {
			if (this->mapa->seTerminoEtapa() && this->mapa->seTerminoJuego() && !this->temporizadorEtapa->pasoElTiempoEstablecido()) {
				this->temporizadorEtapa->avanzarTiempo();
			} else {
				this->mapa->setJuegoFinalizado();
			}
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

	EstadoMapa* estadoMapa = this->mapa->createEstado();

	EstadoJuego* estadoJuego = new EstadoJuego(estadoDeAviones, estadoJugadores, estadoPowerUps,
												estadoMapa);

	return estadoJuego;
}