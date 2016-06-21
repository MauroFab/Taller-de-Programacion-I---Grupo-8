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
#include "../servidor1942/src/FakeAvionEnemigo.h"

class Avion {
private:
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
public:

	Avion(int ventanaAncho, int ventalaAlto, AvionView* avionView, BalaView* balaView);
	~Avion();

	//Mover se debe llamar para actualizar el movimiento, si hay que hacer un roll,
	//se sigue haciendo un roll
	//si se tiene que mover se mueve
	//Si hay que disparar mas, dispara

	//Este es uno que valida la colision, y cambia el estado del avion en base a eso
	//Para definir un comportamiento, si esta en colision disparara
	//Se puede cambiar al avionEnemigo por una lista de avionesEnemigo posteriormente

	void mover(FakeAvionEnemigo avionEnemigo);

	//Este mover no considera ningun tipo de colision
	void mover();

	EstadoAvion* getEstado();
	std::list<EstadoProyectil*> getEstadoProyectiles();

	void setPosicion(Posicion pos);
	// La posicion del avión se toma con respecto al (0,0) que está en la esquina inferior izquierda

	//Este metodo llama a uno de los de abajo de acuerdo al evento que recibe
	void realizarAccionEnBaseA(Evento* evento);

private:

	void darVelocidadHaciaArriba();
	void darVelocidadHaciaAbajo();	

	void darVelocidadHaciaLaDerecha();
	void darVelocidadHaciaLaIzquierda();

	void disparar();
	void hacerUnRoll();

	void continuarMovimientoDelAvion();
	void continuarMovimientoDelAvion(FakeAvionEnemigo avionEnemigo);
	void continuarMovimientoDeLosProyectiles();
	void eliminarLosProyectilesQueSalieronDeLaPantalla();
	int velocidad;

	void continuarMovimientoproyectiles(void);

	SuperficieOcupada actualizarPosicionEnX();
	SuperficieOcupada actualizarPosicionEnY();

	void continuarElRoll();

	int centroProyectil;
public:
	BalaView * balaView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_

