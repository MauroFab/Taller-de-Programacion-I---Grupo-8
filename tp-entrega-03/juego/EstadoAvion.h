#pragma once
#ifndef _ESTADOAVION_H_
#define _ESTADOAVION_H_

#include "EstadoProyectil.h"
#include <list>
using namespace std;

#include "../common/IGenericaVO.h"
class EstadoAvion : public IGenericaVO{
private:

	int sizeBytes;
	int id;
	int frame;
	int posX;
	int posY;
	list<EstadoProyectil*> estadosProyectiles;
	
public:
	EstadoAvion();
	EstadoAvion(int id, int frame, int posX, int posY);
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

	list<EstadoProyectil*> getEstadosProyectiles();
//	void setEstadoProyectiles(std::list<EstadoProyectil*> lista);
	void agregarEstadoProyectil(EstadoProyectil* estadoProyectil);

	void toString(TCadena1000 cadena);	
};
#endif //_ESTADOAVION_H_
