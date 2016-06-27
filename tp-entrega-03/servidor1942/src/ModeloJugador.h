#pragma once
#include "../../juego/EstadoJugador.h"

//Por ahora solamente tiene los puntajes del jugador
//En un futuro tendra algo mas de relacion con los equipos tambien

//Hay otra clase llamada jugador del lado del cliente 
//No confundir. Esta se usa en el modelo.
class ModeloJugador
{
public:
	ModeloJugador(int id);
	~ModeloJugador(void);
	EstadoJugador getEstadoJugador();
	void sumarPuntos(int cantidadDePuntos);
	int getId();
private:
	int id;
	int puntajeAcumulado;
};

