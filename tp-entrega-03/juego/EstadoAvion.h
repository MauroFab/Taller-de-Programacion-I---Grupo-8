#pragma once
#ifndef _ESTADOAVION_H_
#define _ESTADOAVION_H_

#include "EstadoProyectil.h"
#include <list>
#include "../common/IGenericaVO.h"

using namespace std;

class EstadoAvion : public IGenericaVO {

private:

	int sizeBytes;
	int id;
	int frame;
	int posX;
	int posY;
	int puntosDeVida;
	list<EstadoProyectil*> estadosProyectiles;
	
public:
	EstadoAvion();
	EstadoAvion(int id, int frame, int puntosDeVida, int posX, int posY);
	~EstadoAvion();

	//No incluye el tamanio de los proyectiles
	int getSizeBytes();
	void calculateSizeBytes();

	void setId(int id);
	int getId();
	void setFrame(int frame);
	int getFrame();
	void setPosX(int posX);
	int getPosX();
	void setPosY(int posY);
	int getPosY();
	void setPuntosDeVida(int puntosDeVida);
	int getPuntosDeVida();

	list<EstadoProyectil*> getEstadosProyectiles();
	void agregarEstadoProyectil(EstadoProyectil* estadoProyectil);

	void toString(TCadena1000 cadena);	
};
#endif //_ESTADOAVION_H_
