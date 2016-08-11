#pragma once

#include "EstadoPowerUp.h"
#include <list>

#include <map>

#include <SDL2\SDL.h>
#include "Textura.h"

class GraficadorPowerUp
{
public:
	GraficadorPowerUp(SDL_Renderer* renderer);
	~GraficadorPowerUp(void);

	void graficarPowerUps(std::list<EstadoPowerUp> &estadoPowerUps);
private:
	//Los power ups son todos cuadraditos de 30x30. Se podría cargar o dejar hardcodeado
	const static int ANCHO = 30;
	const static int ALTO = 30;
	const static int ALTO_PANTALLA = 640;
	//Los cargo de forma fija, otra vez las rutas quedan hardcodeadas.
	std::map<int,Textura*> mapaTexturasPowerUps;
	SDL_Renderer* renderer;
};

