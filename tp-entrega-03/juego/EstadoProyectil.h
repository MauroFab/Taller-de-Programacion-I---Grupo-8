#pragma once
#ifndef _ESTADOPROYECTIL_H_
#define _ESTADOPROYECTIL_H_

#include <stdio.h>
#include <string.h>
#include "../common/IGenericaVO.h"
class EstadoProyectil : public IGenericaVO{
private:
	int sizeBytes;
	int frame;
	int posX;
	int posY;

public:
	//No usar el constructor sin parametos por fuera del protocolo
	EstadoProyectil();
	EstadoProyectil(int frame, int posX, int posY);
	~EstadoProyectil();
	void setId(int id);
	int getId();
	int getSizeBytes();
	void calculateSizeBytes();

	void setFrame(int frame);
	int getFrame();
	void setPosX(int posX);
	int getPosX();
	void setPosY(int posY);
	int getPosY();
	void toString(TCadena1000 cadena);	
};
#endif //_ESTADOPROYECTIL_H_
