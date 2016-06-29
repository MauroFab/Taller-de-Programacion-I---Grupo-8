#include "MovimientoAterrizaje.h"

MovimientoAterrizaje::MovimientoAterrizaje(Posicion* posInicial, Posicion* posFinal, int velocidad) {
	this->posicionInicial = posInicial;
	this->posicionFinal = posFinal;
	this->posicionIntermedia = new Posicion(posicionInicial->getPosX(), posicionInicial->getPosY());
	this->velocidadAvion = velocidad;

	int xAlQueApunto = this->posicionFinal->getPosX();
	int yAlQueApunto = this->posicionFinal->getPosY();

	//Calculo primero para donde apunta el vector velocidad, luego ajusto su norma
	//Esto es la resta entre los vectores posicion
	double xVectorVelocidad = (xAlQueApunto - this->posicionInicial->getPosX() );
	double yVectorVelocidad = (yAlQueApunto - this->posicionInicial->getPosY() );

	ajustarLaNormaDelVector(xVectorVelocidad, yVectorVelocidad, this->velocidadAvion);

	this->velocidadX = xVectorVelocidad;
	this->velocidadY = yVectorVelocidad;
}

MovimientoAterrizaje::~MovimientoAterrizaje(void) {
	delete this->posicionInicial;
	delete this->posicionFinal;
	delete this->posicionIntermedia;
}

void MovimientoAterrizaje::ajustarLaNormaDelVector(double &xVector, double &yVector, double norma) {
	double coeficienteParaAjustarElModulo;
	//Esto sale de plantear que la norma debe ser igual a un numero
	//Y que el x nuevo y el y nuevo deben ser un multiplo de los viejos
	coeficienteParaAjustarElModulo = sqrt(norma/(xVector*xVector+yVector*yVector));
	xVector = xVector * coeficienteParaAjustarElModulo;
	yVector = yVector * coeficienteParaAjustarElModulo;
}

bool MovimientoAterrizaje::hayQueResponderAEventoExterno() {
	return false;
}

int MovimientoAterrizaje::getVelocidadX() {

	this->posicionIntermedia->setPosX(posicionIntermedia->getPosX() + this->velocidadX);

	if (posicionIntermedia->getPosX() == this->posicionFinal->getPosX()) {
		this->velocidadX = 0;
	}

	return static_cast<int>(this->velocidadX);
}

int MovimientoAterrizaje::getVelocidadY() {

	this->posicionIntermedia->setPosY(posicionIntermedia->getPosY() + this->velocidadY);

	if (posicionIntermedia->getPosY() == this->posicionFinal->getPosY()) {
		this->velocidadY = 0;
	}

	return static_cast<int>(this->velocidadY);
}