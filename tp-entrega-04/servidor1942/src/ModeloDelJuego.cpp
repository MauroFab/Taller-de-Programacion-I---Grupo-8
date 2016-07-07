#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios){
	this->cantidadMaximaDeUsuarios = usuarios->getCantidadMaximaDeUsuarios();
	 crearAviones(servidorXml, usuarios);
	
	setPosicionInicialListAvion();
	this->servidorXml = servidorXml;
	this->mapa = new Mapa(this->servidorXml);
	// Crea un temporizador con 7 segundos
	this->temporizadorEtapa = new Temporizador(7);
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
	std::list<FormacionDeEnemigos> formacionesEnPreparacion;
	std::list<AvionEnemigo*> avionesEnemigosEnPreparacion;
	std::list<PowerUp> powerUpsEnPreparacion;

	//Cargo aviones
	AvionEnemigoXml** enemigosXml = servidorXml->getListaEscenario()[i]->getListaEnemigos();
	for(int j = 0; j < servidorXml->getListaEscenario()[i]->getCanEnes(); j++){
		int x = enemigosXml[j]->getPosicion().coorX;
		int y = enemigosXml[j]->getPosicion().coorY;
		if(enemigosXml[j]->getTipo() ==  A_TIPO_BIG){
			avionesEnemigosEnPreparacion.push_back(new AvionBig(x,y));
			}else if(enemigosXml[j]->getTipo() ==  A_TIPO_MIDDLE){
				avionesEnemigosEnPreparacion.push_back(new AvionMiddle(x,y));
			}else if(enemigosXml[j]->getTipo() ==  A_TIPO_FORMACION){
				//Salen de la posicion 500 de alto en el mapa. Son 10 aviones
				FormacionDeEnemigos formacion(10,500,y);
				formacionesEnPreparacion.push_front(formacion);
				avionesEnemigosEnPreparacion.push_back(new AvionMiddle(300,800));
				std::list<AvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
				avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());
				}else if(enemigosXml[j]->getTipo() ==  A_TIPO_MINI){
					avionesEnemigosEnPreparacion.push_back(new AvionMini(x,y));
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

	std::list<FormacionDeEnemigos> formacionesEnPreparacion;
	std::list<AvionEnemigo*> avionesEnemigosEnPreparacion;
	std::list<PowerUp> powerUpsEnPreparacion;

	//A partir de acá es una carga media manual de aviones enemigos
	//Primero armo una formacion
	int cantidadDeAvionesDeLaFormacion = 4;
	int posicionEnElMapa = 800;
	int posicionPantallaSalida = 500;

	//La formacion crea automaticamente todo los aviones, en un futuro servira para validar la destruccion completa de la misma
	FormacionDeEnemigos formacion(cantidadDeAvionesDeLaFormacion,posicionPantallaSalida,posicionEnElMapa);

	//Agrego la formacion a la lista de formaciones, que se usa para chequear los bonus de puntos
	formacionesEnPreparacion.push_front(formacion);
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(300,800));
	//Luego los agrego a los avionesEnemigos del juego, poniendo la lista de aviones de la formacion en la de enemigos del juego
	std::list<AvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
	avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());

	//Creo un avion mediano, 300 y 800 son las coordenadas iniciales
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(300,800));
	//Y otro
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(200,1000));
	//Y otro
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(100,1200));
	//Lo mismo para el grande
	avionesEnemigosEnPreparacion.push_back(new AvionBig(300,800));

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

	std::list<FormacionDeEnemigos> formacionesEnPreparacion;
	std::list<AvionEnemigo*> avionesEnemigosEnPreparacion;
	std::list<PowerUp> powerUpsEnPreparacion;

	//A partir de acá es una carga media manual de aviones enemigos
	//Primero armo una formacion
	int cantidadDeAvionesDeLaFormacion = 4;
	int posicionEnElMapa = 800;
	int posicionPantallaSalida = 500;

	//La formacion crea automaticamente todo los aviones, en un futuro servira para validar la destruccion completa de la misma
	FormacionDeEnemigos formacion(cantidadDeAvionesDeLaFormacion,posicionPantallaSalida,posicionEnElMapa);

	//Agrego la formacion a la lista de formaciones, que se usa para chequear los bonus de puntos
	formacionesEnPreparacion.push_front(formacion);

	//Luego los agrego a los avionesEnemigos del juego, poniendo la lista de aviones de la formacion en la de enemigos del juego
	std::list<AvionEnemigo*> avionesDeLaFormacion =  formacion.getAvionesDeLaFormacion();
	avionesEnemigosEnPreparacion.insert(avionesEnemigosEnPreparacion.end(), avionesDeLaFormacion.begin(), avionesDeLaFormacion.end());

	//Creo un avion mediano, 300 y 800 son las coordenadas iniciales
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(300,800));
	//Y otro
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(200,1000));
	//Y otro
	avionesEnemigosEnPreparacion.push_back(new AvionMiddle(100,1200));
	//Lo mismo para el grande
	avionesEnemigosEnPreparacion.push_back(new AvionBig(300,800));

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
	 delete this->mapa;
	delete this->temporizadorEtapa;

	for (int i = 0; i < cantidadMaximaDeUsuarios; i++) {
		delete this->listAvion[i];
		}
	delete this->listAvion;

	}

void ModeloDelJuego::crearAviones(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios){
	this->listAvion = new Avion*;
	AvionXml** avionXml;
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
		// balaModel = new BalaModel(avionXml[0]);
		// balaView = new BalaView(BalaModel(avionXml[0]), spriteBala);
		AvionView* avionView;
		AvionModel* avionModel;
		SpriteXml* spriteAvion;
		spriteAvion = SpriteXml::findSpriteById(avionXml[i]->getIdSpAvion(),spriteXml,servidorXml->getCanSprs());
		// avionModel = new AvionModel(avionXml[i]);
		// avionView = new AvionView(AvionModel(avionXml[i]), spriteAvion);
		this->listAvion[i] = new Avion(anchoDeLaVentana, altoDeLaVentana, AvionView(AvionModel(avionXml[i]), spriteAvion), BalaView(BalaModel(avionXml[0]), spriteBala), usuarios->getNombreDeUsuarioDeJugador(i));
		}
	}

void ModeloDelJuego::liberarMemoriaEnemigosDelNivel(int nivel){
	std::list<AvionEnemigo*> enemigosDeEsteNivel = enemigosDeLosNiveles[nivel];
	std::list<AvionEnemigo*>::iterator it;
	for(it = enemigosDeEsteNivel.begin(); it != enemigosDeEsteNivel.end(); it++){
		delete (*it);
		}
	}
void ModeloDelJuego::liberarMemoriaEscenarios(){
	for(int i = 0; i < servidorXml->getCanEsc(); i++){
		liberarMemoriaEnemigosDelNivel(i);
		}
	}

void ModeloDelJuego::reiniciarElJuego(){
	this->mapa->reiniciar();
	for (int i = 0; i < cantidadMaximaDeUsuarios; i++) {
		this->listAvion[i]->reiniciar();
		}

	this->setPosicionInicialListAvion();

	liberarMemoriaEscenarios();

	for(int i = 0; i < servidorXml->getCanEsc(); i++){
		preparoEliNivel(i, this->servidorXml);
		}
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

			reiniciarElJuego();

			}
	}

// La posición (0,0) es en la esquina inferior izquierda
void ModeloDelJuego::setPosicionInicialListAvion(){
	Posicion posicionInicial;
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		posicionInicial = Posicion(30 + i*80, 20);
		this->listAvion[i]->setPosicion(posicionInicial);
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

		list<AvionEnemigo*>::iterator it;
		list<SuperficieOcupada> superficies = getSuperficiesOcupadasPorJugadores();
		for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
			(*it)->continuarMovimiento(superficies);
			}

		//Luego de todos los movimientos, chequeo si tengo que bonificar a alguien por destruir
		//una formacion
		list<FormacionDeEnemigos>::iterator itF;
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
				setPosicionInicialListAvion();
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
	std::list<AvionEnemigo*>::iterator it;
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
