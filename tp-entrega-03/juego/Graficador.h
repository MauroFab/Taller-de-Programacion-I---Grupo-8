#pragma once
#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_
#include "GraficadorPuntaje.h"
#include "EstadoJuego.h"
#include "GraficoAvion.h"
#include "GraficoProyectil.h"
#include "GraficoMapa.h"
#include "Textura.h"
#include "../common/view/AvionView.h"
#include "../common/view/BalaView.h"
#include "../common/view/ElementoView.h"
#include "../common/view/FondoView.h"
#include <list>
#include <map>

class Graficador {

public:

	static Graficador* getInstance();

	~Graficador(void);
	
	void graficarJuego(EstadoJuego* estadoJuego, int idDelJugador);

	void inicializar(SDL_Renderer* renderer, int ventanaAncho, int ventanaAlto);
	void agregarDatosAviones(AvionView* *avionView, int canAvionV);
	void agregarDatosBala(BalaView * balaView);
	void agregarDatosMapa(FondoView * fondoView, ElementoView* *listaElementosView, int canElemV, int posicionInicial);

	void reiniciarMapa();
	void actualizarMapa(EstadoMapa* estadoMapa);

private:
	Graficador();
	void graficarAviones(std::list<EstadoAvion*> listaAviones, int idDelJugador);
	void graficarMapa();
	void graficarPuntaje(int puntaje);

	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	int ventanaAncho;
	int ventanaAlto;
	std::map<int, GraficoAvion*> mapaGraficosAvion;
	GraficoProyectil* graficoProyectil;
	GraficoMapa* graficoMapa;

	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles);
};

#endif //_GRAFICADOR_H_