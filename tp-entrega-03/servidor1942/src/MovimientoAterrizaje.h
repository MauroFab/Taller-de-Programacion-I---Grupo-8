#pragma once

#include "../../common/Posicion.h"
#include "Movimiento.h"

class MovimientoAterrizaje : public Movimiento {

public:
	MovimientoAterrizaje(Posicion* posInicial, Posicion* posFinal, int velocidadAvion);
	virtual ~MovimientoAterrizaje(void);
	bool hayQueResponderAEventoExterno();
	int getVelocidadX();
	int getVelocidadY();
private:
	Posicion* posicionInicial;
	Posicion* posicionFinal;
	Posicion* posicionIntermedia;
	int velocidadAvion;
	double velocidadX;
	double velocidadY;
	void ajustarLaNormaDelVector(double &xVector, double &yVector, double norma);
};

