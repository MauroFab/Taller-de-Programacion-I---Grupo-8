#ifndef _SPRITEXML_H_
#define _SPRITEXML_H_
/* @autor sabris
 */

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

class SpriteXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	char * strId;
	char * path;
	int cantidad;
	int ancho;
	int alto;
public:
	SpriteXml();
	SpriteXml(int id,char * strId,char * path,int cantidad, int ancho, int alto);
	virtual ~SpriteXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setStrId(char * strId,char len_strId);
	char * getStrId();
	void setPath(char * path,char len_path);
	void resetPath(char * path,char len_path);
	char * getPath();
	void setCantidad(int cantidad);
	int getCantidad();
	void setAncho(int ancho);
	int getAncho();
	void setAlto(int alto);
	int getAlto();
	
	void toString(TCadena1000 cadena);
};

#endif //_SPRITEXML_H_
