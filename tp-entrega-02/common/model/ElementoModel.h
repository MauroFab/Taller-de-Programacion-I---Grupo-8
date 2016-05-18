#ifndef _ELEMENTOMODEL_H_
#define _ELEMENTOMODEL_H_

/* @autor cbenez
 */

#include "../xml/ElementoXml.h"

class ElementoModel
{
//private:	
public:
	TPosicion posicion;
public:
	ElementoModel();
	ElementoModel(ElementoXml * elementoXml);
	virtual ~ElementoModel();
};

#endif //_ELEMENTOMODEL_H_
