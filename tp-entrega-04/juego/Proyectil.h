#pragma once
#ifndef _PROYECTIL_H_
#define _PROYECTIL_H_
#include <stdio.h>
#include "Textura.h"
#include "EstadoProyectil.h"
#include "../common/view/BalaView.h"
#include "../servidor1942/src/SuperficieOcupada.h"
#include "../servidor1942/src/AvionEnemigo.h"
#include "../servidor1942/src/ModeloJugador.h"
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
	int velocidad;
	// Velocidad del proyectil
	int velocidadX;
	int velocidadY;
	bool mejorado;
	SuperficieOcupada superficie;
	bool huboUnImpacto;
public:
	static const int ANCHO_PROYECTIL_SIN_MEJORA = 7;
	static const int ALTO_PROYECTIL_SIN_MEJORA = 16;
	Proyectil(BalaView& balaView, bool mejorado);
	virtual ~Proyectil(void);
	bool estaEnPantalla();
	void mover();
	void mover(std::list<AvionEnemigo*> &avionesEnemigos, ModeloJugador* jugadorQueDisparo,
			   std::list<PowerUp> &powerUps);
	void setCoordenasDeComienzo(int posX, int posY);
	bool getHuboUnImpacto();
	/**
	 * esta funcion crea nuevos estados
	 * @return un nuevo estado 
	 */
	EstadoProyectil* createEstado();

};
#endif //_PROYECTIL_H_