#include "MainServidor.h"

bool MainServidor::instanceFlag = false;
MainServidor* MainServidor::single = NULL;

struct IdYPunteroAlSocket {
  int id;
  SOCKET* punteroAlSocket;
};

struct StructDelEnviadorDeMensajes {
  IdYPunteroAlSocket idYPunteroAlSocket;
  bool* seCerroLaConexion;
};

MainServidor::MainServidor(){
	//se realiza una inicializacion parcial
	this->usuarios = NULL;
	this->seDebeCerrarElServidor = true;
	this->puerto = -1;
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
void MainServidor::parsearArchivoXml(int argc, char* argv[]){
	ParserXml parserx;
	parserx.cargarXmlServidor(argc,argv);
	int res = parserx.validarXmlArchivoServidor();
	if (res < 0){
		printf("\nERROR: Error semantico\n");
	}
	else{
		//luego de la carga crea los datos a partir del XML
		ServidorXml * servidorXml = parserx.createDataServidorXml();
		printf("\nOK\n");
		static int cantidadDeClientesMaxima = servidorXml->getCantidadMaximaClientes();
		this->puerto = servidorXml->getPuerto();
		this->usuarios = new AsignadorDeUsuarios(cantidadDeClientesMaxima);
		this->seDebeCerrarElServidor = false;
		
		// luego de usarlo se debe borrar
		delete servidorXml;
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
	local.sin_port = htons(this->puerto); // htons(9999);
	
	//asociamos el socket al puerto
	if (bind(sock, (SOCKADDR*) &local, sizeof(local))==-1){
		printf("error en el bind\n");
		Log::getInstance()->error(" asociando el socket al puerto.");
	}

	return sock;
}

void MainServidor::ponerAEscuchar(SOCKET sock){
	if (listen(sock,2)==-1){
		printf("error en el listen\n");
		Log::getInstance()->error(" al iniciar el listen.");
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

int MainServidor::revisarSiHayMensajesParaElClienteYEnviarlos(void* structPointer)
{
	StructDelEnviadorDeMensajes structRecibido = *((StructDelEnviadorDeMensajes*) structPointer);
	IdYPunteroAlSocket idYPunteroAlSocket = structRecibido.idYPunteroAlSocket;

	//idYPunteroAlSocket es igual a la direccion de memoria apuntada por el puntero recibido
	SOCKET socket = *idYPunteroAlSocket.punteroAlSocket;
	
	//el socket es igual a la direccion apuntada por el punteroAlSocket
	int id = idYPunteroAlSocket.id;
	std::queue<char*>* colaDeMensajesParaEnviar;
	char* mensaje;
	bool* seCerroLaConexionPointer = structRecibido.seCerroLaConexion;
	colaDeMensajesParaEnviar = usuarios->obtenerColaDeUsuario(id);
	
	printf("Se esta preparado para enviar mensajes al usuario: %i\n",id); 
	
	while(!(*seCerroLaConexionPointer)){

		if(!colaDeMensajesParaEnviar->empty()){
			
			mensaje = colaDeMensajesParaEnviar->front();
			SDL_mutexP(mut);
			colaDeMensajesParaEnviar->pop();
			SDL_mutexV(mut);
			send(socket, mensaje, strlen(mensaje), 0 );

			//Aca debería liberar la memoria del mensaje, pero si lo hago estalla.
			//Y efectivamente si mando muchos mensajes (Con un solo cliente abierto), la memoria aumenta, asi que 
			// la estamos perdiendo con los mensajes
		}
	}
    
	return 0;
}

int MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->revisarSiHayMensajesParaElClienteYEnviarlos(idYPunteroAlSocketRecibido);	
}

int MainServidor::fun_consolaDelServidor(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->consolaDelServidor(punteroAlSocketRecibido);	
}
/*
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
}*/

void MainServidor::guardarElMensajeEnLaColaPrincipal(char* buffer, int id){

	SDL_mutexP(mut);
	MensajeConId* mensajeConId = new MensajeConId;
	mensajeConId->id = id;	
	mensajeConId->mensaje = buffer;
	colaDeMensaje.push(mensajeConId);
	SDL_mutexV(mut);
}

int MainServidor::atenderCliente(void* idYPunteroAlSocketRecibido)
{
	int len;
	char Buffer[1024];
	SDL_mutex *mut;
	SDL_Thread* threadDeEnvioDeMensajes;
	mut=SDL_CreateMutex();
	StructDelEnviadorDeMensajes* structParaEnviar = new StructDelEnviadorDeMensajes;
	bool* seCerroLaConexion = new bool;

	//Si bien seCerroLaConexion es algo que se accede de dos threads y puede ser bloqueado con un semaforo
	//No es relevante, una desincronizacion lleva a que se cicle un par de veces demás en el otro thread
	//se perdera mas tiempo bloqueandolo.
	*seCerroLaConexion = false;
	//idYPunteroAlSocket es igual a la direccion de memoria apuntada por el puntero recibido
	IdYPunteroAlSocket idYPunteroAlSocket = *((IdYPunteroAlSocket*) idYPunteroAlSocketRecibido);
	SOCKET socket = *idYPunteroAlSocket.punteroAlSocket;
	int id = idYPunteroAlSocket.id;
	len=sizeof(struct sockaddr);
	structParaEnviar->idYPunteroAlSocket = idYPunteroAlSocket;
	structParaEnviar->seCerroLaConexion = seCerroLaConexion;
	threadDeEnvioDeMensajes =
		SDL_CreateThread(MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos, "mensajesParaElCliente", (void*) structParaEnviar);

	while (len > 0 && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		
		len=recv(socket,Buffer,1023,0); //recibimos los datos que envie
		
		if (len>0){
			//si seguimos conectados
			Buffer[len]=0; //Ponemos el fin de cadena 
			guardarElMensajeEnLaColaPrincipal(Buffer, id);
		}
		else if (len == 0){
			// VER: Mauro *seCerroLaConexion deberia ir aca o es lo mismo que este afuera?
			Log::getInstance()->info( "Se ha desconectado correctamente el usuario " + id);
		}
		else if (len < 0){

			// VER: Mauro *seCerroLaConexion deberia ir aca o es lo mismo que este afuera?
			// Si es -1 hay un error en la conexion
			int error = WSAGetLastError();

			if(error == WSAENOTCONN || error == WSAECONNRESET)
				Log::getInstance()->error( "Se ha desconectado inesperadamente el usuario " + id);
			else if (error == WSAENETDOWN)
				Log::getInstance()->error( "Red caida");
			else
				Log::getInstance()->error( "Error de conexion usuario " + id);
		}
	}
	
	*seCerroLaConexion = true;
	
	// IMPORTANTE: el socket solo se libera cuando se detiene el server, sino no pueden reutilizarse. 
	if(seDebeCerrarElServidor){
		int result = closesocket(socket);
	    WSACleanup();
	}
	
	SDL_WaitThread(threadDeEnvioDeMensajes, NULL);
	delete seCerroLaConexion;
	usuarios->eliminarUsuario(id);

	printf("La cantidad de clientes conectados es: %i\n",usuarios->cantidadDeUsuarios()); 
	Log::getInstance()->info("La cantidad de clientes conectados es: " + usuarios->cantidadDeUsuarios());

	return 0;
}
//----------------------------------------------------------------------------
void freeSockets (SOCKET* s) {  // libero la memoria de los sockets

	Log::getInstance()->debug("Liberando recursos del socket.");
	
	free(s);
}
void waitThread (SDL_Thread* h) {  // wait para todos los threadsockets

	printf("wait al Thread \n");
	Log::getInstance()->debug("Esperando que el thread finalice.");

	SDL_WaitThread(h, NULL);
}
//----------------------------------------------------------------------------
/*
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
			//Problema hace un ingreso innecesario.
			cantidadDeClientes++;
			printf("La cantidad de clientes conectados es: %i\n", cantidadDeClientes); 
			void* punteroAlSocket = socketConexion;
			vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", punteroAlSocket));
			vectorSockets.push_back(socketConexion);
			// colaSockets.push(socketConexion);
			// algun contendor para los hilos que se crean			
		}
	}while(!seDebeCerrarElServidor);
	for_each (vectorHilos.begin(), vectorHilos.end(), waitThread);
	//liberar memoria de los sockets
	for_each (vectorSockets.begin(), vectorSockets.end(), freeSockets);
	return 0;
}*/
int MainServidor::recibirConexiones(void*){
	
	struct sockaddr_in local;

	SOCKET* socketConexion;
	int len = sizeof(struct sockaddr);//Si no pongo esto no funciona, queda para futuras generaciones descubrir porque.

	IdYPunteroAlSocket idYPunteroAlSocket;
	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	Log::getInstance()->debug("En espera de conexiones"); 
	printf("En espera de conexiones\n"); 

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	do{
		if(usuarios->puedoTenerMasUsuarios()){ 
			
			socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket

			*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);

			if (*socketConexion != INVALID_SOCKET) {
			
				printf("Nueva conexion aceptada\n"); 
				Log::getInstance()->info("Nueva conexion acceptada");
			
				// aca chequear los errores por si desconectamos el servidor, cerrando su conexion
				idYPunteroAlSocket.id = usuarios->crearUsuarioYObtenerId();
				printf("La cantidad de clientes conectados es: %i\n",usuarios->cantidadDeUsuarios()); 
				printf("La id del nuevo usuario es: %i\n",idYPunteroAlSocket.id); 
			
				if(usuarios->puedoTenerMasUsuarios()){
					printf("Todavia se pueden tener mas usuarios\n");
				}else{
					printf("Se ha alcanzado el limite de usuarios");
					Log::getInstance()->info("Se ha alcanzado el limite de usuarios.");
				}
			
				idYPunteroAlSocket.punteroAlSocket = socketConexion;

				//VER: Mensaje conexion aceptada
				char* mensaje = "Conexion aceptada.";
				send(*socketConexion, mensaje, strlen(mensaje), 0 );

				vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
				vectorSockets.push_back(socketConexion);
				// colaSockets.push(socketConexion);
				// algun contendor para los hilos que se crean		
			}
			else{
				//VER: revisar si es necesario
				free(socketConexion);
			}

		}
		else {
			// VER: Revisar esta logica
			// Si se supero la cantidad maxima de usuarios enviamos un mensaje al cliente informado que ha sido rechazado

			socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket

			*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);

			if (*socketConexion != INVALID_SOCKET) {

				//VER: Mensaje conexion rechazada
				char* mensaje = "Conexion rechazada. Se ha superado la cantidad maxima de conexiones. Vuelva a intentar mas tarde.";
				send(*socketConexion, mensaje, strlen(mensaje), 0 );

				Log::getInstance()->info("Se informa al cliente que se rechaza la conexion ya que se ha alcanzado el limite de usuarios.");

				vectorSockets.push_back(socketConexion);
			}
			else{
				free(socketConexion);
			}

		}


	}while(!seDebeCerrarElServidor);

	for_each (vectorHilos.begin(), vectorHilos.end(), waitThread);
	//liberar memoria de los sockets
	for_each (vectorSockets.begin(), vectorSockets.end(), freeSockets);

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

	Log::getInstance()->debug("Servidor - Main Principal");

	mut=SDL_CreateMutex();
	MensajeConId* mensajeConId;
	
	printf("Escriba terminar si desea cerrar el servidor\n", usuarios->cantidadDeUsuarios()); 

	SDL_Thread* receptor=SDL_CreateThread(MainServidor::fun_recibirConexiones, "recibirConexiones", NULL);
	SDL_Thread* consola=SDL_CreateThread(MainServidor::fun_consolaDelServidor, "recibirConexiones", NULL);

	Log::getInstance()->debug("Servidor - Main Principal: se inician los thread recibirConexiones");

	while(!seDebeCerrarElServidor){

		SDL_mutexP(mut);

		if(!colaDeMensaje.empty()){

			//consumidor
			std::queue<char*>* colaDeMensajesDelUsuario;
			mensajeConId = colaDeMensaje.front();
			colaDeMensaje.pop();

			printf("Recibido del usuario:%i", mensajeConId->id);
			printf(" el mensaje:%s\n",mensajeConId->mensaje);

			// Log info
			stringstream mensajeLog; 
			mensajeLog << "Usuario " << mensajeConId->id << " Mensaje: " << mensajeConId->mensaje;
			Log::getInstance()->info(mensajeLog.str());

			colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(mensajeConId->id);
			//TODO OJO aca deberia hacerse el delete sino perdera memoria
			//antes fallaba pues pone un puntero a un area de memoria fija y eso es incorrecto
			char* mensajeDeRespuesta = new char[100];

			strcpy(mensajeDeRespuesta,"Llego todo bien");

			SDL_mutexP(mut);
			colaDeMensajesDelUsuario->push(mensajeDeRespuesta);
			SDL_mutexV(mut);
			delete mensajeConId;
		}

		SDL_mutexV(mut);
		SDL_Delay(100);//No quiero tener permanentemente bloqueada la cola para revisar si llego algo.
	}

	Log::getInstance()->info("Se solicito la detención del Server.");

	SDL_WaitThread(receptor, NULL);
	SDL_WaitThread(consola, NULL);

	Log::getInstance()->debug("Servidor - Main Principal: esperando que los threads finalicen.");

	SDL_DestroyMutex(mut);
	SDL_Delay(5000);

	Log::getInstance()->debug("Servidor - Main Principal: se liberaron los recursos.");

	return 0;
}

