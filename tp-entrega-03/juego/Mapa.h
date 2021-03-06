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
	bool seEstaLLegandoAlFinalDeLaEtapa();
	bool empezoUnaNuevaEtapa();
	void setJuegoFinalizado();
	void finalizarJuegoPorEvento();
	void finalizarJuegoPorQueNoHayAviones();
	void reiniciar();
	EstadoMapa* createEstado();
public:
	EstadoMapa* estado;
	int altoVentana;
	int tamanioMaximoMapa;
	int cantidadDePixelesQuePasaron;
	int cantidadEtapas;
	int idEtapaActual;
	bool finalizacionAbrupta;
	bool noHayMasAviones;
};

#endif //_MAPA_H_