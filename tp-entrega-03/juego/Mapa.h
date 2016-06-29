#pragma once

#ifndef _MAPA_H_
#define _MAPA_H_

#include "../juego/EstadoMapa.h"
#include "../common/xml/ServidorXml.h"

#define REINICIO 1
#define NO_REINICIO 0
#define MAX_ALTO_MAPA	2000

class Mapa {

public:

	Mapa(ServidorXml* servidorXml);
	~Mapa();
	void actualizar();
	EstadoMapa* getEstado();
	bool seTerminoEtapa();
	void avanzarEtapa();
	bool seTerminoJuego();
	void setJuegoFinalizado();
//private:
public:
	EstadoMapa* estado;
	int altoVentana;
	int tamanioMaximoMapa;
	int cantidadDePixelesQuePasaron;
	int cantidadEtapas;
	int idEtapaActual;
};

#endif //_MAPA_H_