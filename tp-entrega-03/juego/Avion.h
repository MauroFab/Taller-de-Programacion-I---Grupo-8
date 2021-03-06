#ifndef _AVION_H_
#define _AVION_H_

#include <stdio.h>
#include <string>
#include <list>

#include "Textura.h"
#include "Proyectil.h"
#include "EstadoProyectil.h"
#include "../common/view/AvionView.h"
#include "../common/Posicion.h"
#include "../common/Evento.h"
#include "../servidor1942/src/SuperficieOcupada.h"
#include "../servidor1942/src/AvionEnemigo.h"
#include "../servidor1942/src/ModeloJugador.h"
#include "../servidor1942/src/PowerUp.h"
#include "../servidor1942/src/Movimiento.h"
#include "../servidor1942/src/MovimientoComun.h"
#include "../servidor1942/src/MovimientoAterrizaje.h"
#include "../servidor1942/src/AvionSecundario.h"

class PowerUp;

class Avion {
private:
	//limites de la ventana
	int ventanaAncho;
	int ventanaAlto;
	int anchoAvion;
	int altoAvion;
	int cantDeFotogramas;
	double frame;

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
	bool soyInvulnerable;
	bool tengoElArmaMejorada;
public:

	Avion(int ventanaAncho, int ventalaAlto, AvionView& avionView, BalaView& balaView, string nombreDeUsuario);
	~Avion();

	//Mover se debe llamar para actualizar el movimiento, si hay que hacer un roll,
	//se sigue haciendo un roll
	//si se tiene que mover se mueve
	//Si hay que disparar mas, dispara

	//Este es uno que valida la colision, y cambia el estado del avion en base a eso
	//Se puede cambiar al avionEnemigo por una lista de avionesEnemigo posteriormente

	void mover(list<AvionEnemigo*> &avionesEnemigos, list<PowerUp> &powerUps);

	void cambiarMovimiento(Movimiento* movimiento);

	EstadoJugador getEstadoJugadorAsociado();

	EstadoAvion* getEstado();
	std::list<EstadoProyectil*> getEstadoProyectiles();

	void setPosicion(Posicion pos);
	// La posicion del avi�n se toma con respecto al (0,0) que est� en la esquina inferior izquierda

	//Este metodo llama a uno de los de abajo de acuerdo al evento que recibe
	void realizarAccionEnBaseA(Evento* evento);

	void sumarPuntosAlJugadorAsociado(int puntos);

	void recibirUnImpacto();

	void volverseInvulnerable();
	void dejarDeSerInvulnerable();

	SuperficieOcupada getSuperficieOcupada();

	ModeloJugador* getJugadorAsociado();
	bool estoyDestruido();
	int getVelocidad();
	void reiniciar();

private:

	void darVelocidadHaciaArriba();
	void darVelocidadHaciaAbajo();

	void darVelocidadHaciaLaDerecha();
	void darVelocidadHaciaLaIzquierda();

	void disparar();
	void hacerUnRoll();

	void continuarMovimientoDelAvion();
	void continuarMovimientoDelAvion(list<AvionEnemigo*> &avionesEnemigos,
									 list<PowerUp> &powerUps);
	void continuarMovimientoDeLosProyectiles(std::list<AvionEnemigo*>& avionesEnemigos,
											 std::list<PowerUp> &powerUps);
	void eliminarLosProyectilesQueSalieronDeLaPantalla();
	int velocidad;

	SuperficieOcupada actualizarPosicionEnX();
	SuperficieOcupada actualizarPosicionEnY();

	void continuarElRoll();

	void revisoColisionesConEnemigos(SuperficieOcupada hitbox, list<AvionEnemigo*> &avionesEnemigos,
						  list<PowerUp> &powerUps);
	void revisoColisionesConPowerUps(SuperficieOcupada hitbox, list<PowerUp> &powerUps,
						  list<AvionEnemigo*> &avionesEnemigos);
	void resuelvoColisionConEnemigo(AvionEnemigo* enemigo, list<PowerUp> &powerUps);

	int centroProyectilMejorado;
	int centroProyectilSinMejora;
	
	void destruirEnemigosEnPantalla(list<AvionEnemigo*> &avionesEnemigos);

	void resolverColisionEntreElAvionYElPowerUp(PowerUp &powerUp, 
											    list<AvionEnemigo*> &avionesEnemigos);
	void revisoColisionesConProyectilesDe(AvionEnemigo* enemigo, SuperficieOcupada& hitbox);

	void agregarAvionesSecundarios();

	//No cree una clase jugador completa, y preferi meterla adentro del avion
	//Esto es porque de esta forma puedo resolver los puntajes cuando colisiono en el mover
	//Y porque facilita la comunicacion en el protocolo
	//Entonces un avion tiene un jugadorAsociado, el cual esta jugando con �l
	ModeloJugador* jugadorAsociado;
	Movimiento* logicaDeMovimiento;
	AvionSecundario* avionSecundario1;
	AvionSecundario* avionSecundario2;

public:
	BalaView balaView; //[AGREGACION] NO eliminar
};
#endif //_AVION_H_