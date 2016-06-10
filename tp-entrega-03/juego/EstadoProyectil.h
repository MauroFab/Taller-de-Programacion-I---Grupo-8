#pragma once
#ifndef _ESTADOPROYECTIL_H_
#define _ESTADOPROYECTIL_H_

class EstadoProyectil {

public:
	//No usar el constructor sin parametos por fuera del protocolo
	EstadoProyectil();
	EstadoProyectil(int frame, int posX, int posY);
	~EstadoProyectil(void);

	int getFrame();
	int getPosX();
	int getPosY();

	void setFrame(int frame);
	void setPosX(int x);
	void setPosY(int y);

	int getSizeBytes();
private:
	int frame;
	int x;
	int y;
};
#endif //_ESTADOPROYECTIL_H_
