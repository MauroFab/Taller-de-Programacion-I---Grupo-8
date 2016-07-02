#include "FormacionDeEnemigos.h"


FormacionDeEnemigos::FormacionDeEnemigos(int cantidadDeAvionesEnLaFormacion, 
												 int posicionDeLaPantallaEnLaQueSalen,
											   	 int posicionDelMapaEnLaQueEmpiezanASalir)
{
	for(int i = 0; i < cantidadDeAvionesEnLaFormacion; i++){
		int posicionDesdeLaQueSaleEsteAvion;
		AvionDeFormacion* esteAvion;
		//Voy retrasando la salida para que salgan uno atras del otro
		posicionDesdeLaQueSaleEsteAvion = posicionDelMapaEnLaQueEmpiezanASalir + 
										  i*distanciaEntreAviones;
		esteAvion = new AvionDeFormacion(posicionDesdeLaQueSaleEsteAvion,
															posicionDeLaPantallaEnLaQueSalen);
		this->avionesDeLaFormacion.push_back(esteAvion);
	}
	entreguePuntos = false;
}

list<AvionEnemigo*> FormacionDeEnemigos::getAvionesDeLaFormacion(){
	return avionesDeLaFormacion;
}

bool FormacionDeEnemigos::todosLosAvionesFueronDestruidosPorUnMismoAvion(){
	list<AvionEnemigo*>::iterator it;
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

int FormacionDeEnemigos::obtenerIdDelQueDestruyoAlPrimero(){
	return((avionesDeLaFormacion.front())->getIdDelQueMeDestruyo());
}

FormacionDeEnemigos::~FormacionDeEnemigos(void)
{
}

bool FormacionDeEnemigos::getEntreguePuntos(){
	return entreguePuntos;
}

void FormacionDeEnemigos::entregarPuntosAlJugadorQueDestruyoLaFormacion(Avion** avion){
	int idDelQueLaDestruyo =  obtenerIdDelQueDestruyoAlPrimero();
	avion[idDelQueLaDestruyo]->getJugadorAsociado()->sumarPuntos(puntosQueDaDerribarLaFormacion);
	entreguePuntos = true;
}