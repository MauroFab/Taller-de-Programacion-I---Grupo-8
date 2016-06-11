#pragma once
#ifndef _ESTADOAVION_H_
#define _ESTADOAVION_H_

#include "EstadoProyectil.h"
#include <list>

class EstadoAvion {
private:

	int id;
	int frame;
	int x;
	int y;
	std::list<EstadoProyectil*> estadosProyectiles;
	
	int calcularSizeBytes();
public:
	EstadoAvion();
	EstadoAvion(int id, int frame, int posX, int posY);
	~EstadoAvion(void);

	int getId();
	int getFrame();
	int getPosX();
	int getPosY();
	std::list<EstadoProyectil*> EstadoAvion::getEstadosProyectiles();

	//No incluye el tamanio de los proyectiles
	int getSizeBytes();

	void setId(int id);
	void setFrame(int frame);
	void setPosX(int posX);
	void setPosY(int posY);
	void setEstadoProyectiles(std::list<EstadoProyectil*> lista);
	void agregarEstadoProyectil(EstadoProyectil* estadoProyectil);

};
#endif //_ESTADOAVION_H_
