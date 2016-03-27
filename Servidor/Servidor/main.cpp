#include <iostream>
#include <string>
#include "Servidor_Socket.h"
#include <WinSock2.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <queue>     
#include <iostream>
#undef main

int cantidadDeClientes = 0;
static int cantidadDeClientesMaxima = 3;
bool seDebeCerrarElServidor = false;
std::queue<char*> colaDeMensaje;
std::queue<SOCKET*> colaSockets;
SOCKET socketDeEscucha;
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
	SDL_mutex *mut;
	mut=SDL_CreateMutex();
	SOCKET* punteroAlSocket = (SOCKET*)punteroAlSocketRecibido;
	len=sizeof(struct sockaddr);
   	while (len!=0 && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		len=recv(*punteroAlSocket,Buffer,1023,0); //recibimos los datos que envie
		if (len>0){
		 //si seguimos conectados
			Buffer[len]=0; //le ponemos el final de cadena
			SDL_mutexP(mut);
			colaDeMensaje.push(Buffer);
			printf("Texto recibido:%s\n",Buffer); //imprimimos la cadena recibida
			SDL_mutexV(mut);
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

	// SOCKET socketDeEscucha;
	SOCKET* socketConexion;
	
	int len;
	len=sizeof(struct sockaddr);//Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	do{
		if(cantidadDeClientes < cantidadDeClientesMaxima){ 
			socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket
			*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
			// aca chequear los errores por si desconectamos el servidor, cerrando su conexion
			cantidadDeClientes++;
			printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
			void* punteroAlSocket = socketConexion; // no lo quite pero esta demas
			SDL_CreateThread(atenderCliente, "atenderAlCliente", punteroAlSocket);
			colaSockets.push(socketConexion);
			// algun contendor para los hilos que se crean
			if(seDebeCerrarElServidor==true){
				
				break;
			}
		}
	}while(true);
	//aca tendria que ir, liberar memoria de los sockets, esperar terminar los hilos
	return 0;
}

static int consolaDelServidor(void*){
	char entradaTeclado[20];
	do{
		scanf("%s", entradaTeclado);
	}while(strcmp(entradaTeclado,"terminar"));
		
	seDebeCerrarElServidor = true;
	closesocket(socketDeEscucha);
	return 0;
}
int main(){
	SDL_mutex *mut;
	mut=SDL_CreateMutex();
	char* mensaje;
	printf("Escriba terminar si desea cerrar el servidor\n", cantidadDeClientes); 
	SDL_Thread* receptor = SDL_CreateThread(recibirConexiones, "recibirConexiones", NULL);
	SDL_Thread* consola= SDL_CreateThread(consolaDelServidor, "consolaDelServidor", NULL);
	// me parece que el hilo main deberia de gestionar la consola.
	while(!seDebeCerrarElServidor){
		SDL_mutexP(mut);
		if(!colaDeMensaje.empty()){
			mensaje = colaDeMensaje.front();
			colaDeMensaje.pop();
		}
		SDL_mutexV(mut);
		SDL_Delay(100);//No quiero tener permanentemente bloqueada la cola para revisar si llego algo.
	}
	SDL_WaitThread(receptor, NULL);
	SDL_WaitThread(consola, NULL);
	SDL_DestroyMutex(mut);
	SDL_Delay(1000); // Doy un segundo para que todos los threads lleguen a cerrarse
    return 0;
}
