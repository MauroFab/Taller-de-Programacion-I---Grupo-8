#ifndef _FONDOXML_H_
#define _FONDOXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#include "../IGenericaVO.h"

class FondoXml : public IGenericaVO
{
private:
	int sizeBytes;
	int idSprite;//spriteId:id numerico del sprite
	char * strIdSprite;//spriteId:cadena q contiene el nombre
	int ancho;
	int alto;	
public:
	FondoXml();
	FondoXml(int idSprite,char * strIdSprite,int ancho,int alto);
	virtual ~FondoXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setIdSprite(int idSprite);
	int getIdSprite();
	void setStrIdSprite(char * strIdSprite,int len_strIdSprite);
	char * getStrIdSprite();
	void setAncho(int ancho);
	int getAncho();
	void setAlto(int alto);
	int getAlto();
	
	FondoXml & FondoXml::operator = (const FondoXml & source);
	void toString(TCadena1000 cadena);

};

#endif //_FONDOXML_H_
