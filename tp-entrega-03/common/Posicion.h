#ifndef _POSICION_H_
#define _POSICION_H_
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "IGenericaVO.h"

using namespace std;

class Posicion  : public IGenericaVO{

private:
    int x;
    int y;
	int sizeBytes;
public:
	Posicion();
    Posicion(int x, int y);
	Posicion(const Posicion& p):x(p.x),y(p.y),
	sizeBytes(p.sizeBytes){};
	void Posicion::operator=(const Posicion &p){this->x=p.x; this->y=p.y;
	this->sizeBytes=p.sizeBytes;};
    virtual ~Posicion();
    int getPosX();
    int getPosY();
	void setPosX(int x);
	void setPosY(int y);
	int getSizeBytes();
	void calculateSizeBytes();
	void toString(TCadena1000 cadena);
};

#endif //_POSICION_H_

