#include "MainServidor.h"

bool MainServidor::instanceFlag = false;
MainServidor* MainServidor::single = NULL;

MainServidor::MainServidor(){
	cantidadDeClientes = 0;
	cantidadDeClientesMaxima = 3;
	seDebeCerrarElServidor = false;
}

MainServidor::~MainServidor(){
	instanceFlag = false;
}

MainServidor* MainServidor::getInstance(){
    if(! instanceFlag){
        single = new MainServidor();
        instanceFlag = true;
        return single;
    }
    else{
        return single;
    }
}

SOCKET MainServidor::obtenerSocketInicializado(sockaddr_in &local){
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

void MainServidor::ponerAEscuchar(SOCKET sock){
	if (listen(sock,2)==-1){
		printf("error en el listen\n");
	}
}
int MainServidor::fun_atenderCliente(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->atenderCliente(punteroAlSocketRecibido);	
}

int MainServidor::fun_recibirConexiones(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->recibirConexiones(punteroAlSocketRecibido);	
}


int MainServidor::fun_consolaDelServidor(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->consolaDelServidor(punteroAlSocketRecibido);	
}


int MainServidor::atenderCliente(void* punteroAlSocketRecibido)
{
	int len;
//	SOCKET socket;
	char Buffer[1024];
	SDL_mutex *mut;

	SOCKET* punteroAlSocket = (SOCKET*)punteroAlSocketRecibido;
	len=sizeof(struct sockaddr);
   	while (len!=0 && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		len=recv(*punteroAlSocket,Buffer,1023,0); //recibimos los datos que envie
		//printf("BUG-000");
		if (len>0){
		 //si seguimos conectados
			Buffer[len]=0; //le ponemos el final de cadena
			mut=SDL_CreateMutex();
			//productor
			colaDeMensaje.push(Buffer);
			printf("Texto recibido:%s\n",Buffer); //imprimimos la cadena recibida
			SDL_DestroyMutex(mut);
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


int MainServidor::recibirConexiones(void*){
	struct sockaddr_in local;

	SOCKET socketDeEscucha;
	SOCKET socketConexion;
	int len;
	len=sizeof(struct sockaddr);//Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	do{
		printf("BUG-001");
		if(cantidadDeClientes < cantidadDeClientesMaxima){ 
			socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
			cantidadDeClientes++;
			printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
			void* punteroAlSocket = &socketConexion;
			SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", punteroAlSocket);
		}
	}while(true);
	return 0;
}

int MainServidor::consolaDelServidor(void*){
	char entradaTeclado[20];
	do{
		scanf("%s", entradaTeclado);
	}while(strcmp(entradaTeclado,"terminar"));
	seDebeCerrarElServidor = true;
	return 0;
}

int MainServidor::mainPrincipal(){
	
	SDL_mutex *mut;
	char* mensaje;
	printf("Escriba terminar si desea cerrar el servidor %d\n", cantidadDeClientes); 
	
	SDL_CreateThread(MainServidor::fun_recibirConexiones, "recibirConexiones", NULL);
	SDL_CreateThread(MainServidor::fun_consolaDelServidor, "recibirConexiones", NULL);
	
	while(!seDebeCerrarElServidor){
		//printf("BUG-002");
		mut=SDL_CreateMutex();
		if(!colaDeMensaje.empty()){
			//consumidor
			mensaje = colaDeMensaje.front();
			colaDeMensaje.pop();
		}
		SDL_DestroyMutex(mut);
		SDL_Delay(100);//No quiero tener permanentemente bloqueada la cola para revisar si llego algo.
	}
	SDL_Delay(1000); // Doy un segundo para que todos los threads lleguen a cerrarse
	
    return 0;
}
