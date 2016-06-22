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
	virtual ~UtilJuego();
	//valor entre 0..1
	double fRandom();
	int calcRandom(int desde, int hasta);
	double piso(double arg1);
	double techo(double arg1);
};

#endif //_UTILJUEGO_H_
