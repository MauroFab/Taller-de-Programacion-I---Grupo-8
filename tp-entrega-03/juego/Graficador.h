#pragma once

#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include "EstadoJuego.h"
#include "GraficoAvion.h"
#include "GraficoProyectil.h"
#include "GraficoMapa.h"
#include "GraficadorPuntaje.h"
#include "GraficadorPuntosVida.h"
#include "GraficadorPowerUp.h"
#include "Textura.h"
#include "Etiqueta.h"
#include "../common/view/AvionView.h"
#include "../common/view/BalaView.h"
#include "../common/view/ElementoView.h"
#include "../common/view/FondoView.h"
#include "../common/view/EscenarioView.h"
#include <list>
#include <map>

#define MAX_CANTIDAD_ESCENARIOS 10

class Graficador {

public:

	static Graficador* getInstance();

	~Graficador(void);
	
	void graficarJuego(EstadoJuego* estadoJuego, int idDelJugador);

	void inicializar(SDL_Renderer* renderer, int ventanaAncho, int ventanaAlto);
	void agregarDatosAviones(AvionView* *avionView, int canAvionV);
	void agregarDatosBala(BalaView * balaView);
	void agregarDatosMapa(EscenarioView ** listaEscenariosView, int canEscenariosV, int posicionInicial);

	void reiniciarMapa();
	void actualizarMapa(EstadoMapa* estadoMapa);

private:
	Graficador();
	void graficarAviones(std::list<EstadoAvion*> listaAviones, int idDelJugador);
	void graficarMapa();
	void graficarPuntaje(int puntaje);
	void graficoProyectilConLaTexturaHardcodeada(EstadoProyectil* estadoProyectil);
	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	int ventanaAncho;
	int ventanaAlto;
	std::map<int, GraficoAvion*> mapaGraficosAvion;

	GraficoProyectil* graficoProyectilMejorado;
	Textura* texturaProyectilSinMejora;

	//grafico actual del mapa
	GraficoMapa* graficoMapa;
	//vector de grafico de mapas
	GraficoMapa* graficosMapa[MAX_CANTIDAD_ESCENARIOS];
	GraficadorPuntaje* graficoPuntaje;
	GraficadorPuntosVida* graficoPuntosVida;
	GraficadorPowerUp* graficadorPowerUp;
	bool estaDestruidoElAvion(EstadoAvion* estadoAvion);
	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles, bool esElMejorado);

	EstadoAvion* obtengoElEstadoAvionDelClienteYGraficoLosDemasAviones
								(std::list<EstadoAvion*> listaAviones,int idDelJugador);
	void graficoElAvionDelCliente(EstadoAvion* estadoAvion);
	void graficoLosPuntosDeVidaDelAvionDeEsteCliente(EstadoAvion* estadoAvion);

	int buscarPuntajeDelJugadorEn(EstadoJuego* estadoJuego, int id);
};

#endif //_GRAFICADOR_H_