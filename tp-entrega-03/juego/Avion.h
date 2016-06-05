#pragma once
#ifndef _AVION_H_
#define _AVION_H_

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <string>

//************************
//esto NOO tiene que estar
#define FAKE_POS_X 200
#define FAKE_POS_Y 400
//************************

#include "Textura.h"
#include "Proyectil.h"
#include "ConfiguracionJuegoXML.h"
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include "../common/view/AvionView.h"
#include "../common/Posicion.h"
#include <list>

class Avion {

    public:

		static Avion* getInstance();

		~Avion();

		void mover();
		void render();
		EstadoAvion* getEstado();
		std::list<EstadoProyectil*> getEstadoProyectiles();
		void setPosicion(Posicion pos);
		void inicializar(SDL_Renderer* renderer,int ventanaAncho,int ventanaAlto,AvionView * avionView);

		void darVelocidadHaciaArriba();
		void quitarVelocidadHaciaArriba();
		
		void darVelocidadHaciaAbajo();
		void quitarVelocidadHaciaAbajo();

		void darVelocidadHaciaLaDerecha();
		void quitarVelocidadHaciaLaDerecha();

		void darVelocidadHaciaLaIzquierda();
		void quitarVelocidadHaciaLaIzquierda();

		void disparar();
		void hacerUnRoll();

    private:
		int velocidad;
		static bool instanceFlag;
		static Avion* instance;
		Avion();

		SDL_Rect *fotogramas;
		Textura* texturaAvion;
		SDL_Renderer* renderer;
		//limites de la ventana
		int ventanaAncho;
		int ventanaAlto;
		int frame;

		bool rollFlag;
		std::list<Proyectil*> proyectiles;
		// Posicion del avion
		int posicionX;
		int posicionY;
//		int velocidad;
		// Velocidad del avion
		int velocidadX;
		int velocidadY;
	public:
		AvionView * avionView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_
