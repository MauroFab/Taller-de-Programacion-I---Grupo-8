#pragma once
#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include "Movimiento.h"
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include "GraficoAvion.h"
#include "GraficoProyectil.h"
#include "Textura.h"
#include <list>
#include <map>

class Graficador {

public:

	static Graficador* getInstance();

	~Graficador(void);

	void inicializar(SDL_Renderer* renderer);
	void cargarDatosAvion(int id, std::string pathAvion, int cantFotogramas, int ancho, int alto);
	void cargarDatosProyectil(std::string pathProyectil, int cantFotogramas, int ancho, int alto);
	void graficarAviones(std::map<int,EstadoAvion*> listaAviones);

private:

	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	std::map<int, GraficoAvion*> graficosAvion;

	GraficoProyectil* graficoProyectil;

	Graficador(void);

	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles);
};

#endif //_GRAFICADOR_H_