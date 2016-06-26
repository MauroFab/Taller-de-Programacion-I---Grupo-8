#pragma once
#ifndef _PROYECTIL_H_
#define _PROYECTIL_H_
#include <stdio.h>
#include "Textura.h"
#include "EstadoProyectil.h"
#include "../common/view/BalaView.h"
//************************
//esto NOO tiene que estar

#define FAKE_2_SCREEN_HEIGHT 640
//************************
class Proyectil {
private:
	int frame;
	int cantDeFotogramas;
	int anchoFotograma;
	int altoFotograma;
	// Posicion del proyectil
	int posicionX;
	int posicionY;
	int velocidad;
	// Velocidad del proyectil
	int velocidadX;
	int velocidadY;
	bool mejorado;
public:
	static const int ANCHO_PROYECTIL = 11;
	static const int ALTO_PROYECTIL = 25;
	Proyectil(BalaView * balaView, bool mejorado);
	virtual ~Proyectil(void);
	bool estaEnPantalla();
	void mover();
	void setCoordenasDeComienzo(int posX, int posY);
	/**
	 * esta funcion crea nuevos estados
	 * @return un nuevo estado 
	 */
	EstadoProyectil* createEstado();

};
#endif //_PROYECTIL_H_