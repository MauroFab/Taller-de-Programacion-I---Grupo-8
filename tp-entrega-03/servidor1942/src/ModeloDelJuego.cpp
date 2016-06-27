#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios){
	this->cantidadMaximaDeUsuarios = cantidadMaximaDeUsuarios;
	crearAviones(servidorXml);
	setPosicionInicialListAvion();
	this->mapa = new Mapa(servidorXml);
	//Creo un avionEnemigo fijo para probar la colision
	 avionesEnemigos.push_back(new FakeAvionEnemigo(200,500,68,120,2));
	 avionesEnemigos.push_back(new FakeAvionEnemigo(100,800,68,120,2));
	 avionesEnemigos.push_back(new FakeAvionEnemigo(300,800,68,120,2));
	 avionesEnemigos.push_back(new FakeAvionBig(300,800));
	//Creo un powerUp fijo para probar la colision
	 powerUps.push_back(PowerUp(10,1000,500, TIPO_PUNTOS));
	 powerUps.push_back(PowerUp(100,800,500, TIPO_PUNTOS));
	 powerUps.push_back(PowerUp(200,600,500, TIPO_PUNTOS));
	 powerUps.push_back(PowerUp(300,400,500, TIPO_AMETRALLADORA));
}

ModeloDelJuego::~ModeloDelJuego(){
	delete this->avionEnemigoBeta;
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

void ModeloDelJuego::actualizarMovimientos(){
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		this->listAvion[i]->mover(avionesEnemigos, powerUps);
	}
	this->mapa->actualizar();
	std::list<EstadoPowerUp> estadoPowerUps;
	std::list<PowerUp>::iterator itP;
	for (itP = powerUps.begin(); itP != powerUps.end(); itP++) {
		(*itP).continuarMovimiento();
	}

	list<FakeAvionEnemigo*>::iterator it;
	for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
		(*it)->continuarMovimiento();
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