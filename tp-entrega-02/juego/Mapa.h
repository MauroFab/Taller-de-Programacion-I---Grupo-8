#pragma once
#include "Textura.h"
#include "ElementoDelMapa.h"
#include "ConfiguracionJuegoXML.h"
#include <list>

class Mapa
{
public:

	static Mapa* getInstace();

	void inicializar(SDL_Renderer* renderer);
	void reiniciar();
	~Mapa();
	void graficar();
	//Las posiciones del mapa empiezan en la 1,1 que es la esquina inferior izquierda.
	void crearIslaEn(int x, int y);
	void crearCarrierEn(int x, int y);

private:

	static bool instanceFlag;
	static Mapa* instance;

	Mapa();

	Textura* texturaMapa;
	Textura* texturaIsla;
	Textura* texturaCarrier;
	int anchoMapa;
	int altoMapa;
	int pixelesAvanzados;
	int scrollingOffset;
	int tamanioMaximoMapa;
	SDL_Renderer* renderer;
	int cantidadDePixelesQuePasaron;
	std::list<ElementoDelMapa*> elementosDelMapa;
	void graficarElementosDelMapa();
};
