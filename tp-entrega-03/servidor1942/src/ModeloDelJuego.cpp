#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios){
	this->cantidadMaximaDeUsuarios = cantidadMaximaDeUsuarios;
	crearAviones(servidorXml);
	setPosicionInicialListAvion();
	this->mapa = new Mapa(servidorXml);
	//Creo un avionEnemigo fijo para probar la colision
	 avionesEnemigos.push_back(FakeAvionEnemigo(200,200,68,120,1));
}

ModeloDelJuego::~ModeloDelJuego(){

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
		this->listAvion[i]->mover(avionesEnemigos);
	}
	this->mapa->actualizar();
}

EstadoAvion* ModeloDelJuego::getEstadoAvionJugador(int idAvion){
	return this->listAvion[idAvion]->getEstado();
}

EstadoJuego* ModeloDelJuego::obtenerEstadoDelJuego(){
	//Agrego los aviones de los jugadores
	std::list<EstadoAvion*> estadoDeAviones;
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		estadoDeAviones.push_back(this->listAvion[i]->getEstado());
	}

	//Agrego los avionesEnemigos
	std::list<FakeAvionEnemigo>::iterator it;
	for (it = avionesEnemigos.begin(); it != avionesEnemigos.end(); it++) {
		estadoDeAviones.push_back((*it).getEstado());
	}
	EstadoMapa* estadoMapa = this->mapa->getEstado();
	//Vacia por ahora
	std::list<EstadoJugador> estadoJugador;

	EstadoJuego* estadoJuego = new EstadoJuego(estadoDeAviones, estadoMapa, estadoJugador);

	return estadoJuego;
}