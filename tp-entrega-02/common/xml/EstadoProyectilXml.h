#ifndef _ESTADOPROYECTILXML_H_
#define _ESTADOPROYECTILXML_H_

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

typedef char TCadena1000[1000];

class EstadoProyectilXml 
{
protected:
	int sizeBytes;
	int frame;
	int posX;
	int posY;

public:
	
	EstadoProyectilXml();
	EstadoProyectilXml(int frame, int posX, int posY);
	virtual ~EstadoProyectilXml();
    
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

#endif //_ESTADOPROYECTILXML_H_
