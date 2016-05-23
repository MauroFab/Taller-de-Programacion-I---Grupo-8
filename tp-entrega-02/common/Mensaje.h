#ifndef _MENSAJE_H_
#define _MENSAJE_H_

#include "IGenericaVO.h"

#define MENSAJE_TIPO_VALOR 1
#define MENSAJE_SERVIDOR   2
#define MENSAJE_ESTADO_AVION 3

class Mensaje : public IGenericaVO
{
protected: 
	int id;
	int sizeBytes;
public:
	Mensaje();
	virtual ~Mensaje();

	virtual int getSizeBytes();
	virtual void calculateSizeBytes();
	virtual void setId(int id);
	virtual int getId();

	virtual void toString(TCadena1000 cadena);
	// Retorna el tipo de mensaje que se esta enviado (clave-valor, movimientos, configuracion)
	virtual int getTipo();
};

#endif //_MENSAJE_H_

