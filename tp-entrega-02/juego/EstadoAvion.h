#pragma once
#ifndef _ESTADOAVION_H_
#define _ESTADOAVION_H_

#include "EstadoProyectil.h"

#include <list>

class EstadoAvion {

public:
	
	EstadoAvion(int id, int frame, int posX, int posY);
	~EstadoAvion(void);

	int getId();
	int getFrame();
	int getPosX();
	int getPosY();
	std::list<EstadoProyectil*> EstadoAvion::getEstadosProyectiles();

	void setId(int id);
	void setFrame(int frame);
	void setPosX(int posX);
	void setPosY(int posY);
	void agregarEstadoProyectil(EstadoProyectil* estadoProyectil);

private:

	int id;
	int frame;
	int x;
	int y;
	std::list<EstadoProyectil*> estadosProyectiles;
};
#endif //_ESTADOAVION_H_
