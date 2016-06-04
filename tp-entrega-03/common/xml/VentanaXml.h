#ifndef _VENTANAXML_H_
#define _VENTANAXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

class VentanaXml : public IGenericaVO
{
private:
	int sizeBytes;
	int ancho;
	int alto;
	int velocidadCamara;
public:
	VentanaXml();
	VentanaXml(int ancho,int alto,int velocidadCamara);
	virtual ~VentanaXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setAncho(int ancho);
	int getAncho();
	void setAlto(int alto);
	int getAlto();
	void setVelocidadCamara(int velocidadCamara);
	int getVelocidadCamara();
		//para la misma clase
    VentanaXml & operator = (const VentanaXml & source);
    

	void toString(TCadena1000 cadena);
};

#endif //_VENTANAXML_H_
