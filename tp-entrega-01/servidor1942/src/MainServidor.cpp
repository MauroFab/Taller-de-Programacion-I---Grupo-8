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


	SOCKET* punteroAlSocket = (SOCKET*)punteroAlSocketRecibido;
	len=sizeof(struct sockaddr);
	while (len!=0 && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		len=recv(*punteroAlSocket,Buffer,1023,0); //recibimos los datos que envie
		//printf("BUG-000");
		if (len>0){
			//si seguimos conectados
			Buffer[len]=0; //le ponemos el final de cadena
			SDL_mutexP(mut);
			//productor
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


int MainServidor::recibirConexiones(void*){
	struct sockaddr_in local;

	SOCKET* socketConexion;
	int len;
	len=sizeof(struct sockaddr);//Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	do{
		//printf("BUG-001\n");
		if(cantidadDeClientes < cantidadDeClientesMaxima){ 
			socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket
			*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
			cantidadDeClientes++;
			printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
			void* punteroAlSocket = socketConexion;
			SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", punteroAlSocket);
			// colaSockets.push(socketConexion);
			// algun contendor para los hilos que se crean			
		}
		if(seDebeCerrarElServidor==true){		
			break;
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
	//cuando cierro la conexion del socketDeEscucha, se crea igual un hilo, no controlo eso.
	closesocket(socketDeEscucha);
	return 0;
}

int MainServidor::mainPrincipal(){
	mut=SDL_CreateMutex();
	char* mensaje;
	printf("Escriba terminar si desea cerrar el servidor\n", cantidadDeClientes); 

	SDL_Thread* receptor=SDL_CreateThread(MainServidor::fun_recibirConexiones, "recibirConexiones", NULL);
	SDL_Thread* consola=SDL_CreateThread(MainServidor::fun_consolaDelServidor, "recibirConexiones", NULL);

	while(!seDebeCerrarElServidor){
		//printf("BUG-002");
		SDL_mutexP(mut);
		if(!colaDeMensaje.empty()){
			//consumidor
			mensaje = colaDeMensaje.front();
			colaDeMensaje.pop();
		}
		SDL_mutexV(mut);
		SDL_Delay(100);//No quiero tener permanentemente bloqueada la cola para revisar si llego algo.
	}
	SDL_WaitThread(receptor, NULL);
	SDL_WaitThread(consola, NULL);
	SDL_DestroyMutex(mut);
	return 0;
}
