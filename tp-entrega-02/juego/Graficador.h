#pragma once
#include "Constantes.h"
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
	void graficarMovimientos(std::list<Movimiento*> listaAviones);
	void graficarAviones(std::list<EstadoAvion*> listaAviones);
	void graficarProyectiles(std::list<EstadoProyectil*> listaProyectiles);

private:

	static bool instanceFlag;
	static Graficador* instance;

	SDL_Renderer* renderer;
	std::map<int, GraficoAvion*> graficosAvion;

	GraficoProyectil* graficoProyectil;

	Graficador(void);
};

