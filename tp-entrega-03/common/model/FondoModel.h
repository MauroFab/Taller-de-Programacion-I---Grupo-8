#ifndef _FONDOMODEL_H_
#define _FONDOMODEL_H_
/* @autor cbenez
 */
#include "../xml/FondoXml.h"

class FondoModel {

public:
	int posicionY;//indica la posicion actual sobre el eje de las Y
public:
	FondoModel();
	FondoModel(FondoXml * fondoXml);
	virtual ~FondoModel();
};

#endif //_FONDOMODEL_H_
