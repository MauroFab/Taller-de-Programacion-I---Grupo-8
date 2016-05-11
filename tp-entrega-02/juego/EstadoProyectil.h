#pragma once
#ifndef _ESTADOPROYECTIL_H_
#define _ESTADOPROYECTIL_H_

class EstadoProyectil {

public:

	EstadoProyectil(int frame, int posX, int posY);
	~EstadoProyectil(void);

	int getFrame();
	int getPosX();
	int getPosY();

private:

	int frame;
	int x;
	int y;
};
#endif //_ESTADOPROYECTIL_H_
