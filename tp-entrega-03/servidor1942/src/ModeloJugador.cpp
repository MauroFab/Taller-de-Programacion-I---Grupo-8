#include "ModeloJugador.h"


ModeloJugador::ModeloJugador(int id, string nombre){
	this->id = id;
	this->puntajeAcumulado = 0;
	this->nombreDeUsuario = nombre;
	this->equipo = ConfiguracionInicialJuego::getInstance()->getEquipoDeJugador(this->id);
}

ModeloJugador::~ModeloJugador(){
}

int ModeloJugador::getId(){
	return id;
}

void ModeloJugador::sumarPuntos(int cantidadDePuntos){
	this->puntajeAcumulado += cantidadDePuntos;
}

EstadoJugador ModeloJugador::getEstadoJugador(){
	return(EstadoJugador(id,puntajeAcumulado,equipo,nombreDeUsuario));
}