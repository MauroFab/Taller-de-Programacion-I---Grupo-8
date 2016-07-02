#pragma once

#include "AvionDeFormacion.h"
#include <list>
#include "../../juego/Avion.h"

//Cumple 2 funciones, poder crear todos los aviones de una formacion juntos
//Y luego servira para revisar si toda la formacion fue destruida
class FormacionDeEnemigos
{
public:
	FormacionDeEnemigos(int cantidadDeAvionesEnLaFormacion, 
							int posicionDeLaPantallaEnLaQueSalen,
							int posicionDelMapaEnLaQueEmpiezanASalir);
	~FormacionDeEnemigos(void);
	list<AvionEnemigo*> getAvionesDeLaFormacion();

	bool todosLosAvionesFueronDestruidosPorUnMismoAvion();
	bool getEntreguePuntos();
	//todosLosAvionesFueronDestruidosPorUnMismoAvion() debe devolver verdadero
	void entregarPuntosAlJugadorQueDestruyoLaFormacion(Avion** aviones);
private:
	static const int puntosQueDaDerribarLaFormacion = 500;
	bool entreguePuntos;
	int obtenerIdDelQueDestruyoAlPrimero();
	static const int distanciaEntreAviones = 15;
	list<AvionEnemigo*> avionesDeLaFormacion;
};

