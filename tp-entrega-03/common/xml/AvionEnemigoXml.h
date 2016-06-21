#ifndef _AVIONENEMIGOXML_H_
#define _AVIONENEMIGOXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

#define A_TIPO_BIG			1
#define A_TIPO_FORMACION	2
#define A_TIPO_MIDDLE		3
#define A_TIPO_MINI			4

class AvionEnemigoXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int idSprite;//spriteId:id numerico del sprite
	char * strIdSprite;//spriteId:cadena q contiene el nombre
	TPosicion posicion;
	int tipo;
public:
	AvionEnemigoXml();
	AvionEnemigoXml(int idSprite,char * strIdSprite,int coorX,int coorY,int tipo);
	AvionEnemigoXml(const AvionEnemigoXml&avionEne);
	virtual ~AvionEnemigoXml();

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
	void setTipo(int tipo);
	int getTipo();
    AvionEnemigoXml & operator = (const AvionEnemigoXml & source);
	void toString(TCadena1000 cadena);
};

#endif //_AVIONENEMIGOXML_H_
