#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "Posicion.h"


/**
 * @autor cbenez
 */
//esta clase contiene los datos propios de cada jugador
//en la etapa2 solo el id del cliente 

class Jugador
{
private:
	int idCliente;
	Posicion poscion;
public:
	Jugador();
	virtual ~Jugador();
	string nombreDeUsuario;

	void setIdCliente(int idCliente);
	int getIdCliente();

	void setPosicionAvion(Posicion posicion);
	Posicion getPosicion();
};

#endif //_JUGADOR_H_
