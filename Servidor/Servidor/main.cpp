#include <iostream>
#include <string>
#include "Servidor_Socket.h"
#include <WinSock2.h>
#include <SDL.h>
#include <SDL_thread.h>
#undef main

int cantidadDeClientes = 0;
static int cantidadDeClientesMaxima = 3;
bool seDebeCerrarElServidor = false;
SOCKET obtenerSocketInicializado(sockaddr_in &local){
	WSADATA wsa;
	SOCKET sock;
	//Inicializamos
	WSAStartup(MAKEWORD(2,0),&wsa);
	//Creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//defnimos direcci�n por defecto, ipv4 y el puerto 9999
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(9999);
	//asociamos el socket al puerto
	if (bind(sock, (SOCKADDR*) &local, sizeof(local))==-1){
		printf("error en el bind\n");
	}
	return sock;
}

void ponerAEscuchar(SOCKET sock){
	if (listen(sock,2)==-1){
		printf("error en el listen\n");
	}
}

static int atenderCliente(void* punteroAlSocketRecibido)
{
	int len;
	SOCKET socket;
	char Buffer[1024];
	SOCKET* punteroAlSocket = (SOCKET*)punteroAlSocketRecibido;
	len=sizeof(struct sockaddr);
   	while (len!=0 && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		len=recv(*punteroAlSocket,Buffer,1023,0); //recibimos los datos que envie
		if (len>0){
		 //si seguimos conectados
			Buffer[len]=0; //le ponemos el final de cadena
			printf("Texto recibido:%s\n",Buffer); //imprimimos la cadena recibida
		}
	}
	if(seDebeCerrarElServidor){
		closesocket(*punteroAlSocket);
	    WSACleanup();
	}
	cantidadDeClientes--;
	printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
    return 0;
}

static int recibirConexiones(void*){
	struct sockaddr_in local;

	SOCKET socketDeEscucha;
	SOCKET socketConexion;
	int len;
	len=sizeof(struct sockaddr);//Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	do{
		if(cantidadDeClientes < cantidadDeClientesMaxima){ 
			socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
			cantidadDeClientes++;
			printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
			void* punteroAlSocket = &socketConexion;
			SDL_CreateThread(atenderCliente, "atenderAlCliente", punteroAlSocket);
		}
	}while(true);
}

static int consolaDelServidor(void*){
	char entradaTeclado[20];
	do{
		scanf("%s", entradaTeclado);
	}while(strcmp(entradaTeclado,"terminar"));
	seDebeCerrarElServidor = true;
	return 0;
}
int main(){

	printf("Escriba terminar si desea cerrar el servidor\n", cantidadDeClientes); 
	SDL_CreateThread(recibirConexiones, "recibirConexiones", NULL);
	SDL_CreateThread(consolaDelServidor, "recibirConexiones", NULL);
	while(!seDebeCerrarElServidor){
		SDL_Delay(100); //Ac� va la l�gica principal del programa 
	}
	SDL_Delay(1000); // Doy un segundo para que todos los threads lleguen a cerrarse
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