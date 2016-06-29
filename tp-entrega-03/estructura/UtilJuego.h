#ifndef _UTILJUEGO_H_
#define _UTILJUEGO_H_

#define MAX_VAL_RAND 1000

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
class UtilJuego
{
private:
	static UtilJuego* instance;
	UtilJuego();
public:
	static UtilJuego* getInstance();
	static void liberar();
	virtual ~UtilJuego();
	//valor entre 0..1
	double fRandom();
	int calcRandom(int desde, int hasta);
	double piso(double arg1);
	double techo(double arg1);
	void updatePolarToCartesiana(double v_hipot,double v_ang,double * pX,double * pY);
};

#endif //_UTILJUEGO_H_
