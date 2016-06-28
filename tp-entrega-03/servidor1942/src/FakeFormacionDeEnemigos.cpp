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
	entreguePuntos = false;
}

list<FakeAvionEnemigo*> FakeFormacionDeEnemigos::getAvionesDeLaFormacion(){
	return avionesDeLaFormacion;
}

bool FakeFormacionDeEnemigos::todosLosAvionesFueronDestruidosPorUnMismoAvion(){
	list<FakeAvionEnemigo*>::iterator it;
	it = avionesDeLaFormacion.begin();
	bool fueronDestruidosPorElMismo = true;
	int idDelQueDestruyoAlPrimero;
	bool mireElPrimero = false;
	while(it != avionesDeLaFormacion.end() && fueronDestruidosPorElMismo){
		//Si uno no esta destruido, todos nos fueron destruidos por un mismo avion
		fueronDestruidosPorElMismo = (*it)->estaDestruido();
		if(!mireElPrimero){
			idDelQueDestruyoAlPrimero = (*it)->getIdDelQueMeDestruyo();
		}else{
			fueronDestruidosPorElMismo = (idDelQueDestruyoAlPrimero == (*it)->getIdDelQueMeDestruyo());
		}
		it++;
	}
	return fueronDestruidosPorElMismo;
}

int FakeFormacionDeEnemigos::obtenerIdDelQueDestruyoAlPrimero(){
	return((avionesDeLaFormacion.front())->getIdDelQueMeDestruyo());
}

FakeFormacionDeEnemigos::~FakeFormacionDeEnemigos(void)
{
}

bool FakeFormacionDeEnemigos::getEntreguePuntos(){
	return entreguePuntos;
}

void FakeFormacionDeEnemigos::entregarPuntosAlJugadorQueDestruyoLaFormacion(Avion** avion){
	int idDelQueLaDestruyo =  obtenerIdDelQueDestruyoAlPrimero();
	avion[idDelQueLaDestruyo]->getJugadorAsociado()->sumarPuntos(puntosQueDaDerribarLaFormacion);
	entreguePuntos = true;
}