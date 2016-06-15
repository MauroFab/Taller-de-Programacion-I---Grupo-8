#ifndef _AVION_H_
#define _AVION_H_

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <string>
#include "Textura.h"
#include "Proyectil.h"
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include "../common/view/AvionView.h"
#include "../common/Posicion.h"
#include <list>
#include "../common/Evento.h"
#include "../servidor1942/src/SuperficieOcupada.h"

class Avion {

    public:

		Avion(int ventanaAncho, int ventalaAlto, AvionView* avionView, BalaView* balaView);
		~Avion();

		//Se debe llamar para actualizar el movimiento, si hay que hacer un roll,
		//se sigue haciendo un roll
		//si se tiene que mover se mueve
		//Si hay que disparar mas, dispara
		void mover();

		EstadoAvion* getEstado();
		std::list<EstadoProyectil*> getEstadoProyectiles();
		void setPosicion(Posicion pos);
		// La posicion del avión se toma con respecto al (0,0) que está en la esquina inferior izquierda

		//Este metodo llama a uno de los de abajo de acuerdo al evento que recibe
		void realizarAccionEnBaseA(Evento* evento);

    private:

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

		void continuarMovimientoDelAvion();
		void continuarMovimientoDeLosProyectiles();
		void eliminarLosProyectilesQueSalieronDeLaPantalla();
		int velocidad;

		//limites de la ventana
		int ventanaAncho;
		int ventanaAlto;
		int anchoAvion;
		int altoAvion;
		int cantDeFotogramas;
		int frame;

		bool rollFlag;
		std::list<Proyectil*> proyectiles;
		// Posicion del avion
		SuperficieOcupada superficieQueOcupo;
		// Velocidad del avion
		int velocidadX;
		int velocidadY;
		int id;
		void continuarMovimientoproyectiles(void);
		void actualizarPosicionEnX();
		void actualizarPosicionEnY();
		void continuarElRoll();
	public:
		BalaView * balaView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_

