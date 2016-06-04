#ifndef _ELEMENTOXML_H_
#define _ELEMENTOXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

class ElementoXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int idSprite;//spriteId:id numerico del sprite
	char * strIdSprite;//spriteId:cadena q contiene el nombre
	TPosicion posicion;
public:
	ElementoXml();
	ElementoXml(int idSprite,char * strIdSprite,int coorX,int coorY);
	ElementoXml(const ElementoXml&elemento);
	virtual ~ElementoXml();
	
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setIdSprite(int idSprite);
	int getIdSprite();
	void setStrIdSprite(char * strIdSprite, int len_strIdSprite);
	char * getStrIdSprite();
	void setPosicion(TPosicion posicion);
	TPosicion getPosicion();
	
			//para la misma clase
    ElementoXml & operator = (const ElementoXml & source);
	
	void toString(TCadena1000 cadena);
};

#endif //_ELEMENTOXML_H_
