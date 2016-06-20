#pragma once
#ifndef _ESTADOAVION_H_
#define _ESTADOAVION_H_

#include "EstadoProyectil.h"
#include <list>

class EstadoAvion {
private:

	int sizeBytes;
	int id;
	int frame;
	int posX;
	int posY;
	std::list<EstadoProyectil*> estadosProyectiles;
	
	
public:
	EstadoAvion();
	EstadoAvion(int id, int frame, int posX, int posY);
	~EstadoAvion();

	std::list<EstadoProyectil*> EstadoAvion::getEstadosProyectiles();

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
	void setEstadoProyectiles(std::list<EstadoProyectil*> lista);
	void agregarEstadoProyectil(EstadoProyectil* estadoProyectil);

};
#endif //_ESTADOAVION_H_
