#pragma once

#include "FakeAvionDeFormacion.h"
#include <list>
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

