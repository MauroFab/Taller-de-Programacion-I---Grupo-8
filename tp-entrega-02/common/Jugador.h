#ifndef _JUGADOR_H_
#define _JUGADOR_H_
/**
 * @autor cbenez
 */
//esta clase contiene los datos propios de cada jugador
//en la etapa2 solo el id del cliente 
class Jugador
{
private:
	int idCliente;
public:
	Jugador();
	virtual ~Jugador();
	void setIdCliente(int idCliente);
	int getIdCliente();
};

#endif //_JUGADOR_H_
