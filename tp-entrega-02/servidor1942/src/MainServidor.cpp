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
	this->servidorXml = NULL;
}

MainServidor::~MainServidor(){
	instanceFlag = false;
	// luego de usarlo se debe borrar
	if (servidorXml != NULL)
		delete servidorXml;	
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
		parserx.cargarXmlServidor(0,argv);
	}

	//luego de la carga crea los datos a partir del XML
	this->servidorXml = parserx.createDataServidorXml();
	printf("\nOK\n");
	static int cantidadDeClientesMaxima = servidorXml->getCantidadMaximaClientes();
	this->puerto = servidorXml->getPuerto();
	this->usuarios = new AsignadorDeUsuarios(cantidadDeClientesMaxima);
	this->seDebeCerrarElServidor = false;
	// luego de usarlo se debe borrar
	//	delete servidorXml;
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
	std::queue<EstadoAvionXml*>* colaDeMensajesParaEnviar;
	EstadoAvionXml* mensaje;
	bool* seCerroLaConexionPointer = structRecibido.seCerroLaConexion;
	colaDeMensajesParaEnviar = usuarios->obtenerColaDeUsuario(id);

	printf("Se esta preparado para enviar mensajes al usuario: %i\n",id); 
	//-----------------------------
	bool mensajeJugar=true;
	MensajeXml mensajeEnvio;
	int size = 0;
	char bufferEnvio[MAX_BUFFER];

	while(!(*seCerroLaConexionPointer)){
	// enviar el inicio del juego a todos los clientes

			if(!colaDeMensajesParaEnviar->empty()){
				mensaje = colaDeMensajesParaEnviar->front();
				SDL_mutexP(mut);
				colaDeMensajesParaEnviar->pop();
				if(mensaje->getId() > -3){
					SDL_mutexV(mut);
					char buffEnvio[MAX_BUFFER];
					mensaje->calculateSizeBytes();
					int sizeEnvio = Protocolo::codificar(*mensaje,buffEnvio);
					MensajeSeguro::enviar(socket, buffEnvio, sizeEnvio);

					//Aca debería liberar la memoria del mensaje, pero si lo hago estalla.
					//Y efectivamente si mando muchos mensajes (Con un solo cliente abierto), la memoria aumenta, asi que 
					// la estamos perdiendo con los mensajes
				}
				delete mensaje; // TODO: probe de nuevo y no estaría rompiendo ... revisar bien!
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

void MainServidor::guardarElMensajeEnLaColaPrincipal(char* buffer, int id,EstadoAvionXml* pMsj){

	SDL_mutexP(mut);
	MensajeConId* mensajeConId = new MensajeConId;
	mensajeConId->id = id;	
	mensajeConId->mensaje = buffer;
	//-------------
	//ojo que aquie se llama al operador (=) no es copia de punteros
	mensajeConId->mensajeXml = *pMsj;
	//-------------
	colaDeMensaje.push(mensajeConId);
	SDL_mutexV(mut);
}

void MainServidor::grabarEnElLogLaDesconexion(int len){
	if (len == 0){
		Log::getInstance()->info( "Se ha desconectado el server");
	}
	else if (len < 0){
		// Si es -1 hay un error en la conexion
		int error = WSAGetLastError();

		if(error == WSAENOTCONN || error == WSAECONNRESET){
			Log::getInstance()->error( "Se ha desconectado inesperadamente el server");
		}
		else if (error == WSAENETDOWN)
			Log::getInstance()->error( "Red caida");
		else
			Log::getInstance()->error( "Error de conexion");
	}
}

bool MainServidor::seguimosConectados(int len){
	return(len > 0);
}

int MainServidor::atenderCliente(void* idYPunteroAlSocketRecibido)
{
	int len;
	char bufferEntrada[MAX_BUFFER];
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
	threadDeEnvioDeMensajes = SDL_CreateThread(MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos, "mensajesParaElCliente", (void*) structParaEnviar);

	bool esElPrimerMensaje = true;
	while (seguimosConectados(len) && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		EstadoAvionXml *pMensj;
		len=MensajeSeguro::recibir(socket,bufferEntrada); //recibimos los datos que envie
		if (seguimosConectados(len)){
			if(!esElPrimerMensaje)
				delete pMensj;
			esElPrimerMensaje = false;
			pMensj = new EstadoAvionXml();
			Protocolo::decodificar(bufferEntrada,pMensj);
			guardarElMensajeEnLaColaPrincipal(bufferEntrada, id,pMensj);
			//--------------------------------
			//bufferEntrada[len]=0; //Ponemos el fin de cadena 

		}else{
			grabarEnElLogLaDesconexion(len);
			// El frame 42 es el grisado
			pMensj->setFrame(42);
			pMensj->eliminarProyectiles();
			guardarElMensajeEnLaColaPrincipal(bufferEntrada, id,pMensj);
			delete pMensj;
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
	usuarios->desconectarUsuario(id);

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
void MainServidor::enviarMensajeDeConexionAceptadaAl(SOCKET* socket){
	char buffEnvio[MAX_BUFFER];
	int size = 0;
	MensajeXml mensajeEnvio;
	mensajeEnvio.setValor(FAKE_MENSAJE_01, strlen(FAKE_MENSAJE_01));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	size = Protocolo::codificar(mensajeEnvio,buffEnvio);
	size += Protocolo::codificar(*this->servidorXml,buffEnvio + size);
	MensajeSeguro::enviar(*socket, buffEnvio, size);
}

void MainServidor::enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket){
	char buffEnvio[MAX_BUFFER];
	int size = 0;
	char* strMsj = FAKE_MENSAJE_02;
	MensajeXml mensaje;
	mensaje.setValor(strMsj,strlen(strMsj));;
	mensaje.calculateSizeBytes();
	mensaje.setTipo(TIPO_STRING);
	int sizeEnvio = Protocolo::codificar(mensaje,buffEnvio);
	MensajeSeguro::enviar(*socket, buffEnvio, sizeEnvio);
}

void MainServidor::enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(SOCKET* socket){
	char buffEnvio[MAX_BUFFER];
	int size = 0;
	MensajeXml mensajeEnvio;
	mensajeEnvio.setValor(FAKE_MENSAJE_03, strlen(FAKE_MENSAJE_03));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	size = Protocolo::codificar(mensajeEnvio, buffEnvio);
	MensajeSeguro::enviar(*socket, buffEnvio, size);
}

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

				// Antes de crear un usuario realizo las validaciones de nombre de usuario
				char bufferEntrada[MAX_BUFFER];

				MensajeSeguro::recibir(*socketConexion, bufferEntrada);

				MensajeXml mensajeUsuario; 

				Protocolo::decodificar(bufferEntrada, &mensajeUsuario);

				char* usuario = mensajeUsuario.getValor();

				// Verifica si está conectado
				MensajeXml mensajeEnvio;
				int size = 0;
				char buffEnvio[MAX_BUFFER];

				// Si ese nombre de usuario existe 
				if(usuarios->nombreDeUsuarioExistente(usuario)){

					// Si ya esta conectado lo rechazo
					if(usuarios->estaConectado(usuario)){
						enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(socketConexion);
					} else { // Sino lo reconectamos

						idYPunteroAlSocket.id = usuarios->reconectar(usuario);
						idYPunteroAlSocket.punteroAlSocket = socketConexion;
						enviarMensajeDeConexionAceptadaAl(socketConexion);
						
						Protocolo::codificar(*(new EstadoAvionXml(-1,0,0,0)), buffEnvio);
						MensajeSeguro::enviar(*socketConexion, buffEnvio, size);
						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
					}				
				}
				else {
						idYPunteroAlSocket.id = usuarios->crearUsuarioYObtenerId(usuario);
						idYPunteroAlSocket.punteroAlSocket = socketConexion;

						printf("La cantidad de clientes conectados es: %d\n",usuarios->cantidadDeUsuarios()); 
						printf("La id del nuevo usuario es: %d\n",idYPunteroAlSocket.id); 

						if(usuarios->puedoTenerMasUsuarios()){
							printf("Todavia se pueden tener mas usuarios\n");
						}else{
							printf("Se ha alcanzado el limite de usuarios");
							Log::getInstance()->info("Se ha alcanzado el limite de usuarios.");
						}

						enviarMensajeDeConexionAceptadaAl(socketConexion);

						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
				}

			}
			else{
				free(socketConexion);
			}
		}
		else {
			// Si se supero la cantidad maxima de usuarios enviamos un mensaje al cliente informado que ha sido rechazado

			socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket
			
			*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);

			if (*socketConexion != INVALID_SOCKET) {

				//VER: Mensaje conexion rechazada
				enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(socketConexion);
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

int MainServidor::fun_avisarATodos(void* data){
	MainServidor * instan = MainServidor::getInstance();
	return instan->avisarATodos(data);	
}


int MainServidor::avisarATodos(void* data){
	std::queue<EstadoAvionXml*>* colaDeMensajesDelUsuario;
	MensajeConId* mensajeConId=(MensajeConId*)data;
	for(int i = 0; i < usuarios->cantidadDeUsuarios(); i++){

		if(i != mensajeConId->id){

			colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
			EstadoAvionXml* mensajeDeRespuesta = new EstadoAvionXml(mensajeConId->mensajeXml.getId(), mensajeConId->mensajeXml.getFrame(), mensajeConId->mensajeXml.getPosX(), mensajeConId->mensajeXml.getPosY());

			SDL_mutexP(mut);
			colaDeMensajesDelUsuario->push(mensajeDeRespuesta);
			SDL_mutexV(mut);
		}
	}
	delete mensajeConId;
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
	bool seHaIniciadoLaPartida = false;
	std::queue<EstadoAvionXml*>* colaDeMensajesDelUsuario;

	while(!seDebeCerrarElServidor && !seHaIniciadoLaPartida){
		//Cuando estoy lleno, le aviso a todos los jugadores que la partida comienza
		if(!usuarios->puedoTenerMasUsuarios()){
			for(int i = 0; i < usuarios->cantidadDeUsuarios(); i++){
				colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
				colaDeMensajesDelUsuario->push(new EstadoAvionXml(-1,0,0,0));
			}
			seHaIniciadoLaPartida = true;
		}
		SDL_Delay(100);
	}

	while(!seDebeCerrarElServidor){

		
		SDL_mutexP(mut);


		if(!colaDeMensaje.empty()){

			//consumidor
			
			mensajeConId = colaDeMensaje.front();
			colaDeMensaje.pop();

			printf("Recibido del usuario:%i", mensajeConId->id);
			printf(" Movimiento id: %d frame: %d x: %d y: %d\n",mensajeConId->mensajeXml.getId(), mensajeConId->mensajeXml.getFrame(), mensajeConId->mensajeXml.getPosX(), mensajeConId->mensajeXml.getPosY());

			// Log info
			stringstream mensajeLog; 
			mensajeLog << "Usuario " << mensajeConId->id << " Movimiento: id: " << mensajeConId->mensajeXml.getId() << " frame: " <<  mensajeConId->mensajeXml.getFrame() << " x: " << mensajeConId->mensajeXml.getPosX() << " y: " << mensajeConId->mensajeXml.getPosY();
			mensajeLog << " SizeBytes:" << mensajeConId->mensajeXml.getSizeBytes();
			Log::getInstance()->debug(mensajeLog.str());

			//TODO OJO aca deberia hacerse el delete sino perdera memoria
			//antes fallaba pues pone un puntero a un area de memoria fija y eso es incorrecto

			// SDL_Thread* avisador=SDL_CreateThread(MainServidor::fun_avisarATodos, "recibirConexiones", (void*)mensajeConId);
	

			for(int i = 0; i < usuarios->cantidadDeUsuarios(); i++){

				if(i != mensajeConId->id){

					colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
					EstadoAvionXml* mensajeDeRespuesta = new EstadoAvionXml(mensajeConId->mensajeXml.getId(), mensajeConId->mensajeXml.getFrame(), mensajeConId->mensajeXml.getPosX(), mensajeConId->mensajeXml.getPosY());

					std::list<EstadoProyectilXml*>::iterator it;
					std::list<EstadoProyectilXml*> listaP = mensajeConId->mensajeXml.getEstadosProyectiles();

					for (it = listaP.begin(); it != listaP.end(); it++) {
						mensajeDeRespuesta->agregarEstadoProyectil(new EstadoProyectilXml((*it)->getFrame(),(*it)->getPosX(), (*it)->getPosY()));
					}

					// SDL_mutexP(mut);
					colaDeMensajesDelUsuario->push(mensajeDeRespuesta);
					// SDL_mutexV(mut);
				}
			}
			delete mensajeConId;
		}

		SDL_mutexV(mut);
		//SDL_Delay(100);//No quiero tener permanentemente bloqueada la cola para revisar si llego algo.
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
