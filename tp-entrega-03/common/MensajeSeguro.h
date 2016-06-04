#ifndef _MENSAJESEGURO_H_
#define _MENSAJESEGURO_H_

#include <WinSock2.h>
#include "Protocolo.h"

class MensajeSeguro
{
public:
	MensajeSeguro();
	virtual ~MensajeSeguro();
	
	static int enviar(SOCKET& sock,char * buffer, int tamanio);
	static int recibir(SOCKET& sock,char* buffer);


};

#endif //_MENSAJESEGURO_H_

