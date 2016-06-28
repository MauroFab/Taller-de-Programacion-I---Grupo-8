#pragma once

#include "../../juego/EstadoJugador.h"
#include "ConfiguracionInicialJuego.h"

//Hay otra clase llamada jugador del lado del cliente 
//No confundir. Esta se usa en el modelo.

class ModeloJugador {

public:
	ModeloJugador(int id);
	~ModeloJugador(void);
	EstadoJugador getEstadoJugador();
	void sumarPuntos(int cantidadDePuntos);
	int getId();
private:
	int id;
	int puntajeAcumulado;
	int equipo;
};

