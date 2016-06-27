#include "FakeFormacionDeEnemigos.h"


FakeFormacionDeEnemigos::FakeFormacionDeEnemigos(int cantidadDeAvionesEnLaFormacion, 
												 int posicionDeLaPantallaEnLaQueSalen,
											   	 int posicionDelMapaEnLaQueEmpiezanASalir)
{
	for(int i = 0; i < cantidadDeAvionesEnLaFormacion; i++){
		int posicionDesdeLaQueSaleEsteAvion;
		FakeAvionDeFormacion* esteAvion;
		//Voy retrasando la salida para que salgan uno atras del otro
		posicionDesdeLaQueSaleEsteAvion = posicionDelMapaEnLaQueEmpiezanASalir + 
										  i*distanciaEntreAviones;
		esteAvion = new FakeAvionDeFormacion(posicionDesdeLaQueSaleEsteAvion,
															posicionDeLaPantallaEnLaQueSalen);
		this->avionesDeLaFormacion.push_back(esteAvion);
	}
}

list<FakeAvionEnemigo*> FakeFormacionDeEnemigos::getAvionesDeLaFormacion(){
	return avionesDeLaFormacion;
}

FakeFormacionDeEnemigos::~FakeFormacionDeEnemigos(void)
{
}
