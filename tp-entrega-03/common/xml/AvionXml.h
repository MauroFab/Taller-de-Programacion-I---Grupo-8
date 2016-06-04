#ifndef _AVIONXML_H_
#define _AVIONXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

class AvionXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int velAvion;//velocidadDesplazamiento	
	int velBala;//velocidadDisparos	
	int idSpAvion;//avionSpriteId
	char * strSpAvion;//avionSpriteId:cadena q contiene el nombre
	int idSpVuelta;//vueltaSpriteId
	char * strSpVuelta;//vueltaSpriteId:cadena q contiene el nombre
	int idSpBala;//disparosSpriteId
	char * strSpBala;//disparosSpriteId:cadena q contiene el nombre
public:
	AvionXml();
	AvionXml(int idxAvion,int velAvion,int velBala,int idSpAvion,char * strSpAvion,int idSpVuelta,char * strSpVuelta,int idSpBala,char * strSpBala);
	virtual ~AvionXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	
	void setVelAvion(int velAvion);
	int getVelAvion();
	void setVelBala(int velBala);
	int getVelBala();
	void setIdSpAvion(int idSpAvion);
	int getIdSpAvion();
	void setStrSpAvion(char * strSpAvion, int len_strSpAvion);
	char * getStrSpAvion();
	void setIdSpVuelta(int idSpVuelta);
	int getIdSpVuelta();
	void setStrSpVuelta(char * strSpVuelta,int len_strSpVuelta);
	char * getStrSpVuelta();
	void setIdSpBala(int idSpBala);
	int getIdSpBala();
	void setStrSpBala(char * strSpBala,int len_strSpBala);
	char * getStrSpBala();
	
	void toString(TCadena1000 cadena);
};

#endif //_AVIONXML_H_
