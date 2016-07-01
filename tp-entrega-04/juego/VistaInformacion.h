#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_image.h>
#include <list>
#include "EstadoJugador.h"
#include "FondoInicio.h"
#include "Etiqueta.h"
#include "..\common\StringUtil.h"

#define FUENTE_PATH "./sfd/DejaVuSans.ttf"

using namespace std;

class VistaInformacion {

public:
	VistaInformacion(void);
	virtual ~VistaInformacion(void);
	virtual void mostrar(std::list<EstadoJugador> estadosJugadores);
	virtual void reiniciar();
protected:
	SDL_Renderer* renderer;
	TTF_Font* font;
	FondoInicio* fondo;
	bool seHaGraficado;
};

