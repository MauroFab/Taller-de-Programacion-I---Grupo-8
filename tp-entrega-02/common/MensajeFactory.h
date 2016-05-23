#ifndef _MENSAJEFACTORY_H_
#define _MENSAJEFACTORY_H_

#include "../juego/EstadoProyectil.h"
#include "../juego/EstadoAvion.h"
#include "Mensaje.h"

class MensajeFactory{

public: 
	static Mensaje* crear(int mensaje);
	static Mensaje* crear(double mensaje);
	static Mensaje* crear(char mensaje);
	static Mensaje* crear(std::string mensaje);
	static Mensaje* crear(EstadoAvion* estado);
};

#endif // MENSAJEFACTORY_H_
