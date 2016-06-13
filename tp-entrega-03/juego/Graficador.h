#pragma once
#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

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

	void inicializar(SDL_Renderer* renderer, int ventanaAncho, int ventanaAlto);
	void agregarDatosAviones(AvionView* *avionView, int canAvionV);
	void agregarDatosBala(BalaView * balaView);
	void graficarAviones(std::map<int,EstadoAvion*> listaAviones);

private:

	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	int ventanaAncho;
	int ventanaAlto;
	std::map<int, GraficoAvion*> mapaGraficosAvion;

	GraficoProyectil* graficoProyectil;
	Graficador(void);
	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles);
};

#endif //_GRAFICADOR_H_