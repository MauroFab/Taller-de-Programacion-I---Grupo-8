#ifndef _AVION_H_
#define _AVION_H_

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <string>
#include "Textura.h"
#include "Proyectil.h"
#include "EstadoProyectil.h"
#include "../common/view/AvionView.h"
#include "../common/Posicion.h"
#include <list>
#include "../common/Evento.h"
#include "../servidor1942/src/SuperficieOcupada.h"
#include "../servidor1942/src/FakeAvionEnemigo.h"
#include "../servidor1942/src/ModeloJugador.h"
#include "../servidor1942/src/PowerUp.h"

class PowerUp;

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

	static const int vidaMaximaAvion = 3;
	int puntosDeVida;
	bool soyInvulnerable, tengoElArmaMejorada;
public:

	Avion(int ventanaAncho, int ventalaAlto, AvionView* avionView, BalaView* balaView);
	~Avion();

	//Mover se debe llamar para actualizar el movimiento, si hay que hacer un roll,
	//se sigue haciendo un roll
	//si se tiene que mover se mueve
	//Si hay que disparar mas, dispara

	//Este es uno que valida la colision, y cambia el estado del avion en base a eso
	//Se puede cambiar al avionEnemigo por una lista de avionesEnemigo posteriormente

	void mover(list<FakeAvionEnemigo> &avionesEnemigos, list<PowerUp> &powerUps);

	

	EstadoJugador getEstadoJugadorAsociado();

	EstadoAvion* getEstado();
	std::list<EstadoProyectil*> getEstadoProyectiles();

	void setPosicion(Posicion pos);
	// La posicion del avión se toma con respecto al (0,0) que está en la esquina inferior izquierda

	//Este metodo llama a uno de los de abajo de acuerdo al evento que recibe
	void realizarAccionEnBaseA(Evento* evento);

	void sumarPuntosAlJugadorAsociado(int puntos);

	void recibirUnImpacto();

	void volverseInvulnerable();
	void dejarDeSerInvulnerable();

private:

	//Este mover no considera ningun tipo de colision, fuera de uso
	void mover();


	void darVelocidadHaciaArriba();
	void darVelocidadHaciaAbajo();

	void darVelocidadHaciaLaDerecha();
	void darVelocidadHaciaLaIzquierda();

	void disparar();
	void hacerUnRoll();

	void continuarMovimientoDelAvion();
	void continuarMovimientoDelAvion(list<FakeAvionEnemigo> &avionesEnemigos,
									 list<PowerUp> &powerUps);
	void continuarMovimientoDeLosProyectiles();
	void eliminarLosProyectilesQueSalieronDeLaPantalla();
	int velocidad;

	void continuarMovimientoproyectiles(void);

	SuperficieOcupada actualizarPosicionEnX();
	SuperficieOcupada actualizarPosicionEnY();

	void continuarElRoll();

	void revisoColisiones(SuperficieOcupada hitbox, list<FakeAvionEnemigo> &avionesEnemigos);
	void revisoColisiones(SuperficieOcupada hitbox, list<PowerUp> &powerUps);

	int centroProyectilMejorado, centroProyectilSinMejora;
	
	void resolverColisionEntreElAvionY(PowerUp &powerUp);

	//No cree una clase jugador completa, y preferi meterla adentro del avion
	//Esto es porque de esta forma puedo resolver los puntajes cuando colisiono en el mover
	//Y porque facilita la comunicacion en el protocolo
	//Entonces un avion tiene un jugadorAsociado, el cual esta jugando con él
	ModeloJugador* jugadorAsociado;
public:
	BalaView * balaView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_

