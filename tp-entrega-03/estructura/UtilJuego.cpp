#include "UtilJuego.h"
UtilJuego * UtilJuego::instance = NULL;

UtilJuego* UtilJuego::getInstance() {
	if(instance == NULL){
        instance = new UtilJuego();
    }
    return instance;
}
UtilJuego::UtilJuego()
{
	srand(time(NULL));
}

UtilJuego::~UtilJuego()
{
	if(instance != NULL){
        delete instance;
    }
}
int UtilJuego::calcRandom(int desde, int hasta){
	int rango = hasta - desde + 1;
	double va = rand() % rango + desde;
	return (int)va;
}
double UtilJuego::fRandom(){
	double val = calcRandom(0,MAX_VAL_RAND);
	val = (val == 0.0 ? 0.0: (val/MAX_VAL_RAND));
	return val;
}
double UtilJuego::piso(double arg1){
	return floor(arg1);
}
double UtilJuego::techo(double arg1){
	return ceil(arg1);
}

void UtilJuego::updatePolarToCartesiana(double v_hipot,double v_ang,double * pX,double * pY){
	double x = v_hipot*cos(v_ang) + *pX;
	double y = v_hipot*sin(v_ang) + *pY;	
	*pX = x;
	*pY = y;
//	printf("\nang=%f x=%f y=%f ",v_ang,x,y);
}
