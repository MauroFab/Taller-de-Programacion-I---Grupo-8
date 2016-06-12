#include "ModeloDelJuego.h"

ModeloDelJuego::ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios){
	this->cantidadMaximaDeUsuarios = cantidadMaximaDeUsuarios;
	crearAviones(servidorXml);
	darPosicionInicialAAviones();
}

ModeloDelJuego::~ModeloDelJuego(){

}

void ModeloDelJuego::crearAviones(ServidorXml* servidorXml){
	avion = new Avion*;
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
		avion[i] = new Avion(anchoDeLaVentana, altoDeLaVentana, avionView, balaView);
	}
}

void ModeloDelJuego::actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento){
	avion[idDelJugadorQueMandoElEvento]->realizarAccionEnBaseA(evento);
}

// La posición (0,0) es en la esquina inferior izquierda
void ModeloDelJuego::darPosicionInicialAAviones(){
	Posicion posicionInicialParaTodos = Posicion(200,50);
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		avion[i]->setPosicion(posicionInicialParaTodos);
	}
}
void ModeloDelJuego::avanzarElTiempo(){
for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		avion[i]->mover();
	}
}

EstadoAvion* ModeloDelJuego::obtenerEstadoDelAvionDelJugador(int id){
	return avion[id]->getEstado();
}

EstadoJuego* ModeloDelJuego::obtenerEstadoDelJuego(){
	std::list<EstadoAvion*> estadoDeAviones;
	for(int i = 0; i < cantidadMaximaDeUsuarios; i++){
		estadoDeAviones.push_back(avion[i]->getEstado());
	}
	EstadoJuego* estadoJuego = new EstadoJuego(estadoDeAviones);
	return estadoJuego;
}