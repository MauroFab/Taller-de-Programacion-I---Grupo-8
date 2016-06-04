#ifndef _ESCENARIOXML_H_
#define _ESCENARIOXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "FondoXml.h"
#include "ElementoXml.h"
#include "../IGenericaVO.h"

#define MAX_ELEMENTOS	300

class EscenarioXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int ancho;
	int alto;
	FondoXml fondoXml;
	//BUG-003 cambiar la lista de elementos
	ElementoXml * lista[MAX_ELEMENTOS];	
	int canElems;
public:
	EscenarioXml();
	virtual ~EscenarioXml();
	//para la misma clase
    EscenarioXml & operator = (const EscenarioXml & source);	
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setAncho(int ancho);
	int getAncho();
	void setAlto(int alto);
	int getAlto();	
	void setFondoXml(const FondoXml &fondoXml);
	/*const */FondoXml * getFondoXmlCopy();
	void addElemento(ElementoXml * elemento,int pos);
	//listado de punteros
	ElementoXml * * getListaElementos();
	int getCanElems();
	
	void toString(TCadena1000 cadena);
};

#endif //_ESCENARIOXML_H_
