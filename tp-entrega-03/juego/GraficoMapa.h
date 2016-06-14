#pragma once

#include <stdio.h>
#include "Textura.h"
#include "ElementoDelMapa.h"
#include "EstadoMapa.h"
#include "../common/view/FondoView.h"
#include "../common/view/ElementoView.h"
#include <list>
#define FONDO_DEFAULT "fondoDefault.bmp"
using namespace std;

class GraficoMapa {

public:

	GraficoMapa(SDL_Renderer* renderer, FondoView * fondoView, int posicionInicial);
	virtual ~GraficoMapa(void);

	Textura* getTextura();
	void crearElementos(ElementoView* *listaElementosView, int canElemV);
	void graficarFondoYElementos();
	void reiniciar();
	void actualizar(EstadoMapa* estadoMapa);

private:

	SDL_Renderer* renderer;
	Textura* textura;
	int tamanioMaximoMapa;
	int anchoMapa;
	int altoMapa;
	int posicionInicial;
	int scrollingOffset;
	int cantidadDePixelesQuePasaron;
	std::list<ElementoDelMapa*> elementosDelMapa;

	void configurarElMapaConLaPosicion(int pos);
	void graficarElementos();
};

