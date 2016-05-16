#ifndef _MENSAJEXML_H_
#define _MENSAJEXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#include "../IGenericaVO.h"

#define TIPO_INT	1
#define TIPO_DOUBLE	2
#define TIPO_STRING	3
#define TIPO_CHAR	4

#define STR_TIPO_INT	"INT"
#define STR_TIPO_DOUBLE	"DOUBLE"
#define STR_TIPO_STRING	"STRING"
#define STR_TIPO_CHAR	"CHAR"

class MensajeXml : public IGenericaVO
{
protected:
	int sizeBytes;
	int id;
	int tipo;
	char * valor;
public:
	MensajeXml();
	MensajeXml(int id,int tipo,char * valor);
	MensajeXml(const MensajeXml&mensaje);
	virtual ~MensajeXml();
	//para la misma clase
    MensajeXml & operator = (const MensajeXml & source);
    
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setTipo(int tipo);
	int getTipo();
	char * getValor();
	void setValor(const char * valor,int lenValor);
	void toString(TCadena1000 cadena);	
};

#endif //_MENSAJEXML_H_
