#pragma once
#ifndef _ESTADOPROYECTIL_H_
#define _ESTADOPROYECTIL_H_

class EstadoProyectil {
private:
	int frame;
	int posX;
	int posY;

public:
	//No usar el constructor sin parametos por fuera del protocolo
	EstadoProyectil();
	EstadoProyectil(int frame, int posX, int posY);
	~EstadoProyectil(void);
	int getSizeBytes();

	void setFrame(int frame);
	int getFrame();
	void setPosX(int posX);
	int getPosX();
	void setPosY(int posY);
	int getPosY();




};
#endif //_ESTADOPROYECTIL_H_
