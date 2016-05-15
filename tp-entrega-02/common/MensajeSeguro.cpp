#include "MensajeSeguro.h"


MensajeSeguro::MensajeSeguro()
{
}
MensajeSeguro::~MensajeSeguro()
{
}

int MensajeSeguro::enviar(SOCKET& sock,char * buffer, int size){
	size_t len=0;
	size_t tamanio=size;
	// cout<<"tamanio enviado:"<<tamanio<<endl;
	len=send(sock,(char*)&tamanio, sizeof(size_t), 0);
	if(len<=0)
		return len;
	len=0;
	size_t acum=0;
	while(acum!=tamanio){
		len=send(sock,buffer+acum,tamanio,0);
		if(len<=0)
			return len;
		acum+=len;
	    // cout<<"tamanio:"<<tamanio<<"acum enviado:"<<acum<<endl;
	}

	return len;
}
int MensajeSeguro::recibir(SOCKET& sock,char* buffer){
	size_t len=0;
	size_t tamanio;
	len=recv(sock,(char*)&(tamanio),sizeof(size_t),0);
	if(len<=0)
		return len;
	// cout<<"tamanio recibido:"<<tamanio<<endl;
	//Aca deberia de poderse reservar memoria dinamica y no trabajar con el buffer estatico, pero
	// por ahora seguira igual
	len=0;
	size_t acum=0;
	while(acum!=tamanio){
		len=recv(sock,buffer+acum,tamanio,0);
		if(len<=0)
			return len;
		acum+=len;
		// cout<<"tamanio:"<<tamanio<<"acum recibido:"<<acum<<endl;
	}
	return len;
}
