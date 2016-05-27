#pragma once
#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include "Movimiento.h"
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include "GraficoAvion.h"
#include "GraficoProyectil.h"
#include "Textura.h"
#include "../common/view/AvionView.h"
#include "../common/view/BalaView.h"
#include <list>
#include <map>

class Graficador {

public:

	static Graficador* getInstance();

	~Graficador(void);

	void inicializar(SDL_Renderer* renderer);
	void agregarDatosAvion(AvionView * avionView);
	void agregarDatosBala(BalaView * balaView);
	void graficarAviones(std::map<int,EstadoAvion*> listaAviones);
	/**
	 * este metodo renderiza todos los aviones que tenga guardado el mapa interno
	 */
	void graficarAvionesAll();

private:

	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	std::map<int, GraficoAvion*> mapaGraficosAvion;

	GraficoProyectil* graficoProyectil;
	Graficador(void);
	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles);
};

#endif //_GRAFICADOR_H_