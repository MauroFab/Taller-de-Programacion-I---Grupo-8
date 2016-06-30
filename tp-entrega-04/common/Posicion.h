#ifndef _POSICION_H_
#define _POSICION_H_
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#include "IGenericaVO.h"
class Posicion  : public IGenericaVO{

private:
    int x;
    int y;
	int sizeBytes;
public:
	Posicion();
    Posicion(int x, int y);
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

