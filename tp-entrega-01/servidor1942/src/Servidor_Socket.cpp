#include "Servidor_Socket.h"

Servidor_Socket::Servidor_Socket(SOCKET& socket):Common_Socket(socket){}
Servidor_Socket::Servidor_Socket(string ip,string port):Common_Socket(ip,port){}
Servidor_Socket::Servidor_Socket(string port):Common_Socket(port){}

int Servidor_Socket::escuchar(){

	//asociamos el socket al puerto
	if (bind(sock, (SOCKADDR*) &local, sizeof(local))==-1)
	{
		printf("error en el bind\n");
		return -1;
	}
	
	//ponemos el socket a la escucha
	if (listen(sock,1)==-1)
	{
		printf("error en el listen\n");
		return -1;
	}


	len=sizeof(struct sockaddr);

	//hay una conexión entrante y la aceptamos
	sock=accept(sock,(sockaddr*)&local,&len);
	printf("[Cuando se vaya recibiendo texto aparecera en pantalla ]\n");
		
	return 0;
}
Servidor_Socket::~Servidor_Socket(void)
{
}
