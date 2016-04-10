#ifndef _MENSAJEXML_H_
#define _MENSAJEXML_H_
#include <stdlib.h>
#include <string.h>

#define TIPO_INT	1
#define TIPO_DOUBLE	2
#define TIPO_STRING	3
#define TIPO_CHAR	4

#define STR_TIPO_INT	"INT"
#define STR_TIPO_DOUBLE	"DOUBLE"
#define STR_TIPO_STRING	"STRING"
#define STR_TIPO_CHAR	"CHAR"

class MensajeXml
{
protected:
	int sizeBytes;
	int id;
	int tipo;
	char * valor;
public:
	MensajeXml();
	MensajeXml(int id,int tipo,char * valor);
	virtual ~MensajeXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setTipo(int tipo);
	int getTipo();
	char * getValor();
	void setValor(char * valor,int lenValor);
};

#endif //_MENSAJEXML_H_
