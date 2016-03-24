#include <iostream>
#include <string>
#include "Servidor_Socket.h"
#include <WinSock2.h>

SOCKET obtenerSocketInicializado(sockaddr_in &local){
	WSADATA wsa;
	SOCKET sock;
	//Inicializamos
	WSAStartup(MAKEWORD(2,0),&wsa);
	//Creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//defnimos dirección por defecto, ipv4 y el puerto 9999
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(9999);
	//asociamos el socket al puerto
	if (bind(sock, (SOCKADDR*) &local, sizeof(local))==-1){
		printf("error en el bind\n");
	}
	//ponemos el socket a la escucha
	if (listen(sock,1)==-1){
		printf("error en el listen\n");
	}
	return sock;
}

int main(){

	struct sockaddr_in local;
	int len=1;
	char Buffer[1024];
	SOCKET socketDeEscucha;
	SOCKET socketConexion;

	len=sizeof(struct sockaddr); //Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	socketDeEscucha = obtenerSocketInicializado(local);
	//Un thread tiene que quedarse en un loop aceptando
	socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
	//Cuando agarra un socketConexion, lo manda a hacer lo que sigue en un thread nuevo.
	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	while (len!=0){ //mientras estemos conectados con el otro pc
		len=recv(socketConexion,Buffer,1023,0); //recibimos los datos que envie
		if (len>0){
		 //si seguimos conectados
			Buffer[len]=0; //le ponemos el final de cadena
			printf("Texto recibido:%s",Buffer); //imprimimos la cadena recibida
		}
	}
return 0;
}

/*{
	int len=-1;
	string datos;
	string ip="localhost";
	string puerto="9999";
	Servidor_Socket Ssocket(ip,puerto);
	Ssocket.escuchar();
	while (len!=0) //mientras estemos conectados con el otro pc
	{
		len=Ssocket.recibir(datos);
		if (strcmp(datos.c_str(),"salir")==0)
			len=0;
	}
	return 0;
}*/