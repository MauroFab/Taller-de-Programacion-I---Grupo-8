#pragma once

#ifndef _MAPA_H_
#define _MAPA_H_

#include "../juego/EstadoMapa.h"
#include "../common/xml/ServidorXml.h"

#define REINICIO 1

class Mapa {

public:

	Mapa(ServidorXml* servidorXml);
	~Mapa();
	void actualizar();
	EstadoMapa* getEstado();

private:

	EstadoMapa* estado;
	int alto;
	int tamanioMaximo;
	int scrollingOffSet;
	int cantidadDePixelesQuePasaron;
};

#endif //_MAPA_H_