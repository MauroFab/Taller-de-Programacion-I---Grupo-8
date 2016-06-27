#pragma once

#include "FakeAvionDeFormacion.h"
#include <list>

//Cumple 2 funciones, poder crear todos los aviones de una formacion juntos
//Y luego servira para revisar si toda la formacion fue destruida
class FakeFormacionDeEnemigos
{
public:
	FakeFormacionDeEnemigos(int cantidadDeAvionesEnLaFormacion, 
							int posicionDeLaPantallaEnLaQueSalen,
							int posicionDelMapaEnLaQueEmpiezanASalir);
	~FakeFormacionDeEnemigos(void);
	list<FakeAvionEnemigo*> getAvionesDeLaFormacion();
private:
	static const int distanciaEntreAviones = 15;
	list<FakeAvionEnemigo*> avionesDeLaFormacion;
};

