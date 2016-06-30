#pragma once

#include "../../juego/EstadoJugador.h"
#include "ConfiguracionInicialJuego.h"
#include <string>

//Hay otra clase llamada jugador del lado del cliente 
//No confundir. Esta se usa en el modelo.

class ModeloJugador {

public:
	ModeloJugador(int id, string nombreDeUsuario);
	~ModeloJugador(void);
	EstadoJugador getEstadoJugador();
	void sumarPuntos(int cantidadDePuntos);
	int getId();
	void reiniciar();
private:
	int id;
	int puntajeAcumulado;
	int equipo;
	string nombreDeUsuario;
};

