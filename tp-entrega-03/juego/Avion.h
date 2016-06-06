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
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include "../common/view/AvionView.h"
#include "../common/Posicion.h"
#include <list>

class Avion {

    public:

		static Avion* getInstance();

		~Avion();

		//Se debe llamar para actualizar el movimiento, si hay que hacer un roll,
		//se sigue haciendo un roll
		//si se tiene que mover se mueve
		//Si hay que disparar mas, dispara
		void mover();

		EstadoAvion* getEstado();
		std::list<EstadoProyectil*> getEstadoProyectiles();
		void setPosicion(Posicion pos);
		void inicializar(SDL_Renderer* renderer,int ventanaAncho,int ventanaAlto,AvionView * avionView);

		//la velocidad debe ser positiva
		//Siendo consciente que sumar velocidad a la izquierda es lo mismo que restar a la derecha
		//Lo dejo por claridad de codigo cuando este pasado el modelo al servidor
		//Y <- Y +/- delta_Y   donde delta_Y es la velocidad en Y
		void darVelocidadHaciaArriba();
		void quitarVelocidadHaciaArriba();
		void darVelocidadHaciaAbajo();	//repetido, eliminar
		void quitarVelocidadHaciaAbajo();//repetido, eliminar

		//Idem comentario anterior
		//X <- X +/- delta_X   donde delta_X es la velocidad en X
		void darVelocidadHaciaLaDerecha();
		void quitarVelocidadHaciaLaDerecha();
		void darVelocidadHaciaLaIzquierda(); //repetido, eliminar
		void quitarVelocidadHaciaLaIzquierda(); //repetido, eliminar

		void disparar();
		//Solamente pone un flag en true, esto es todo lo necesario para marcar que se esta haciendo un roll.
		//Los movimientos se realizan todos con la funcion mover
		//OJO no hace nada, solo indica vuelta=true
		void hacerUnRoll();

    private:

		void continuarMovimientoDelAvion();
		void continuarMovimientoDeLosProyectiles();
		void eliminarLosProyectilesQueSalieronDeLaPantalla();
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
private:
void continuarMovimientoproyectiles(void);
	public:
		AvionView * avionView; //[AGREGACION] NO eliminar
		BalaView * balaView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_

