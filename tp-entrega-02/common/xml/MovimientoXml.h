#ifndef _MOVIMIENTOXML_H_
#define _MOVIMIENTOXML_H_

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "../IGenericaVO.h"

#define TIPO_MOV_AVION		1
#define TIPO_MOV_ROLL		2
#define TIPO_MOV_DISPARO	3

#define STR_TIPO_MOV_AVION		"AVION"
#define STR_TIPO_MOV_ROLL		"ROLL"
#define STR_TIPO_MOV_DISPARO	"DISPARO"

class MovimientoXml : public IGenericaVO
{
protected:
	int sizeBytes;
	int id;
	int tipo;
	int posX;
	int posY;

public:
	
	MovimientoXml();
	MovimientoXml(int id,int tipo, int posX, int posY);
	virtual ~MovimientoXml();
    
	int getSizeBytes();
	void calculateSizeBytes();

	void setId(int id);
	int getId();
	
	void setTipo(int tipo);
	int getTipo();
	
	void setPosX(int posX);
	int getPosX();

	void setPosY(int posY);
	int getPosY();

	void toString(TCadena1000 cadena);	
};

#endif //_MOVIMIENTOXML_H_
