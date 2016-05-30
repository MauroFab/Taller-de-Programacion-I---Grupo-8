#include "MainServidor.h"

bool MainServidor::instanceFlag = false;
MainServidor* MainServidor::single = NULL;

/*-------- Estructuras e inicialización --------*/

struct IdYPunteroAlSocket {
	int id;
	SOCKET* punteroAlSocket;
};

struct StructDelEnviadorDeMensajes {
	IdYPunteroAlSocket idYPunteroAlSocket;
	bool* seCerroLaConexion;
};

MainServidor::MainServidor(){

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
	this->servidorXml = parserx.createDataServidorXml(); //luego de la carga crea los datos a partir del XML
	static int cantidadDeClientesMaxima = servidorXml->getCantidadMaximaClientes();
	this->puerto = servidorXml->getPuerto();
	this->usuarios = new AsignadorDeUsuarios(cantidadDeClientesMaxima);
	this->seDebeCerrarElServidor = false;
	// luego de usarlo se debe borrar
	//	delete servidorXml;	
}

/*-------- Funciones de destrucción de Threads y Sockects --------*/

void freeSockets (SOCKET* s) {

	Log::getInstance()->debug("Liberando recursos del socket.");

	free(s);
}

void waitThread (SDL_Thread* h) {

	printf("wait al Thread \n");
	Log::getInstance()->debug("Esperando que el thread finalice.");

	SDL_WaitThread(h, NULL);
}


/*-------- Funciones estáticas para la llamada de las mismas como puntero a función --------*/

int MainServidor::fun_atenderCliente(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->atenderCliente(punteroAlSocketRecibido);	
}

int MainServidor::fun_recibirConexiones(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->recibirConexiones(punteroAlSocketRecibido);	
}

int MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->revisarSiHayMensajesParaElClienteYEnviarlos(idYPunteroAlSocketRecibido);	
}

int MainServidor::fun_consola(void* punteroAlSocketRecibido){
	MainServidor * instan = MainServidor::getInstance();
	return instan->consola(punteroAlSocketRecibido);	
}

/*-------- Funciones privadas --------*/

SOCKET MainServidor::obtenerSocketInicializado(sockaddr_in &local){

	WSADATA wsa;
	SOCKET sock;

	//Inicializamos
	WSAStartup(MAKEWORD(2,0),&wsa);

	//Creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	//defnimos dirección por defecto, ipv4
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(this->puerto);

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

int MainServidor::revisarSiHayMensajesParaElClienteYEnviarlos(void* structPointer) {

	StructDelEnviadorDeMensajes structRecibido = *((StructDelEnviadorDeMensajes*) structPointer);
	IdYPunteroAlSocket idYPunteroAlSocket = structRecibido.idYPunteroAlSocket;

	//idYPunteroAlSocket es igual a la direccion de memoria apuntada por el puntero recibido
	SOCKET socket = *idYPunteroAlSocket.punteroAlSocket;

	int id = idYPunteroAlSocket.id;
	std::queue<EstadoAvionXml*>* colaDeMensajesParaEnviar;
	EstadoAvionXml* stAvionXml;
	bool* seCerroLaConexionPointer = structRecibido.seCerroLaConexion;
	colaDeMensajesParaEnviar = usuarios->obtenerColaDeUsuario(id);

	printf("Se esta preparando para enviar mensajes al usuario: %i\n",id); 
	//-----------------------------
	bool mensajeJugar=true;
	MensajeXml mensajeEnvio;
//	int size = 0;
//	char bufferEnvio[MAX_BUFFER];

	while(!(*seCerroLaConexionPointer)){
	// enviar el inicio del juego a todos los clientes
		SDL_LockMutex(mutColaDeUsuario[id]);
		if(!colaDeMensajesParaEnviar->empty()){
			stAvionXml = colaDeMensajesParaEnviar->front();
			colaDeMensajesParaEnviar->pop();
			SDL_UnlockMutex(mutColaDeUsuario[id]);
			if(stAvionXml->getId() > -3){
				char buffEnvio[MAX_BUFFER];
				stAvionXml->calculateSizeBytes();
				int sizeEnvio = Protocolo::codificar(*stAvionXml,buffEnvio);
				MensajeSeguro::enviar(socket, buffEnvio, sizeEnvio);
			}
			delete stAvionXml; // TODO: probe de nuevo y no estaría rompiendo ... revisar bien!
		}else{//Si la cola estaba vacía, permito que los demas threads usen la cola
			SDL_UnlockMutex(mutColaDeUsuario[id]);
		}
	}

	return 0;
}

void MainServidor::guardarElMensajeEnLaColaPrincipal(char* buffer, int id, EstadoAvionXml* pMsj){

	MensajeConId* mensajeConId = new MensajeConId;
	mensajeConId->id = id;	
	mensajeConId->mensaje = buffer;
	//-------------
	//ojo que aquie se llama al operador (=) no es copia de punteros
	mensajeConId->estadoAvionXml = *pMsj;
	//-------------
	colaDeMensaje.push(mensajeConId);
}

void MainServidor::grabarEnElLogLaDesconexion(int len){
	SDL_LockMutex(mutLogger);
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
	SDL_UnlockMutex(mutLogger);
}

bool MainServidor::seguimosConectados(int len){
	return(len > 0);
}


int MainServidor::atenderCliente(void* idYPunteroAlSocketRecibido) {

	int len;
	char bufferEntrada[MAX_BUFFER];
	SDL_Thread* threadDeEnvioDeMensajes;
	StructDelEnviadorDeMensajes* structParaEnviar = new StructDelEnviadorDeMensajes;
	bool* seCerroLaConexion = new bool;

	/* Si bien seCerroLaConexion es algo que se accede desde dos threads y puede ser bloqueado con un semaforo
	   no es relevante. Una desincronización lleva a que se cicle un par de veces de más en el otro thread.
	   Se perderá mas tiempo bloqueandolo.
	*/
	*seCerroLaConexion = false;

	//idYPunteroAlSocket es igual a la direccion de memoria apuntada por el puntero recibido
	IdYPunteroAlSocket idYPunteroAlSocket = *((IdYPunteroAlSocket*) idYPunteroAlSocketRecibido);

	SOCKET socket = *idYPunteroAlSocket.punteroAlSocket;
	int id = idYPunteroAlSocket.id;
	len = sizeof(struct sockaddr);
	structParaEnviar->idYPunteroAlSocket = idYPunteroAlSocket;
	structParaEnviar->seCerroLaConexion = seCerroLaConexion;
	threadDeEnvioDeMensajes = SDL_CreateThread(MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos, "mensajesParaElCliente", (void*) structParaEnviar);

	bool esElPrimerMensaje = true;
	while (seguimosConectados(len) && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		
		EstadoAvionXml *stAvionXml;
		len=MensajeSeguro::recibir(socket,bufferEntrada);
		
		if (seguimosConectados(len)){
			if(!esElPrimerMensaje)
				delete stAvionXml;
			esElPrimerMensaje = false;
			stAvionXml = new EstadoAvionXml();
			Protocolo::decodificar(bufferEntrada,stAvionXml);

			// Se actualiza la posicion del avión en el asignador de usuarios
			Posicion posicion;

			posicion.setPosX(stAvionXml->getPosX());
			posicion.setPosY(stAvionXml->getPosY());
			usuarios->setPosicionAUsuario(id, posicion);

			SDL_LockMutex(mutColaPrincipal);
			guardarElMensajeEnLaColaPrincipal(bufferEntrada, id,stAvionXml);
			SDL_UnlockMutex(mutColaPrincipal);

		}else{
			if(!esElPrimerMensaje){
			grabarEnElLogLaDesconexion(len);
			// El frame 42 es el grisado
			stAvionXml->setFrame(42);
			stAvionXml->eliminarProyectiles();
			SDL_LockMutex(mutColaPrincipal);
			guardarElMensajeEnLaColaPrincipal(bufferEntrada, id,stAvionXml);
			SDL_UnlockMutex(mutColaPrincipal);
			delete stAvionXml;
			}
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
	SDL_LockMutex(mutColaDeUsuario[id]);
	usuarios->desconectarUsuario(id);
	SDL_UnlockMutex(mutColaDeUsuario[id]);
	printf("La cantidad de clientes conectados es: %i\n",usuarios->cantidadDeUsuarios()); 

	SDL_LockMutex(mutLogger);
	Log::getInstance()->info("La cantidad de clientes conectados es: " + usuarios->cantidadDeUsuarios());
	SDL_UnlockMutex(mutLogger);

	return 0;
}

void MainServidor::enviarMensajeDeConexionAceptadaAl(int idUsuario, SOCKET* socket){

	// Mensaje de conexion exitosa
	char buffEnvio[MAX_BUFFER];
	int offset = 0;
	MensajeXml mensajeEnvio;
	mensajeEnvio.setValor(FAKE_MENSAJE_01, strlen(FAKE_MENSAJE_01));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	offset = Protocolo::codificar(mensajeEnvio,buffEnvio + offset);

	// ID del usuario
	string idString = StringUtil::intToString(idUsuario);
	mensajeEnvio.setValor((char*)idString.c_str(), strlen(idString.c_str()));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	offset += Protocolo::codificar(mensajeEnvio,buffEnvio + offset);

	// Posicion de inicio
	Posicion* pos;
	Posicion posAEnviar;
	pos = usuarios->getPosicionDeUsuario(idUsuario);
	posAEnviar.setPosX(pos->getPosX());
	posAEnviar.setPosY(pos->getPosY());
	posAEnviar.calculateSizeBytes();
	offset += Protocolo::codificar(posAEnviar, buffEnvio + offset);

	//Posicion del mapa
	
	pos = usuarios->getPosicionDeUsuario(idUsuario);

	//Por ahora la posicion inicial del mapa (En Y es la que importa) queda hardcodeada en 0
	//Hay que tomarla de algun cliente
	Posicion posDelMapa;
	posDelMapa.setPosX(0);
	posDelMapa.setPosY(0);
	posDelMapa.calculateSizeBytes();
	offset += Protocolo::codificar(posDelMapa, buffEnvio + offset);
	// XML de configuracion 
	offset += Protocolo::codificar(*this->servidorXml,buffEnvio + offset);

	MensajeSeguro::enviar(*socket, buffEnvio, offset);
}

void MainServidor::enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket){

	char buffEnvio[MAX_BUFFER];
//	int size = 0;
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

void MainServidor::enviarUnMensajeAvisandoleQueYaEmpezoElJuegoAl(SOCKET* socket){

	char buffEnvio[MAX_BUFFER];
	int size = 0;
	EstadoAvionXml* estadoEmpezoLaPartida = new EstadoAvionXml(-1,0,0,0);
	estadoEmpezoLaPartida->calculateSizeBytes();
	size =Protocolo::codificar(*estadoEmpezoLaPartida, buffEnvio);
	MensajeSeguro::enviar(*socket, buffEnvio, size);
}
int MainServidor::recibirConexiones(void*){

	struct sockaddr_in local;

	SOCKET* socketConexion;
	int len = sizeof(struct sockaddr);

	IdYPunteroAlSocket idYPunteroAlSocket;
	socketDeEscucha = obtenerSocketInicializado(local);
	ponerAEscuchar(socketDeEscucha);

	Log::getInstance()->debug("En espera de conexiones"); 
	printf("En espera de conexiones\n"); 

	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");
	
	do{
		socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket

		*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
		if(usuarios->puedoTenerMasUsuarios()){ 
			if (*socketConexion != INVALID_SOCKET) {

				printf("Nueva conexion aceptada\n"); 
				Log::getInstance()->info("Nueva conexion acceptada");

				// Antes de crear un usuario realizo las validaciones de nombre de usuario
				char bufferEntrada[MAX_BUFFER];

				MensajeSeguro::recibir(*socketConexion, bufferEntrada);

				MensajeXml mensajeUsuario; 

				Protocolo::decodificar(bufferEntrada, &mensajeUsuario);

				char* usuario = mensajeUsuario.getValor();
	
				// Si ese nombre de usuario existe 
				if(usuarios->nombreDeUsuarioExistente(usuario)){

					// Si ya esta conectado lo rechazo
					if(usuarios->estaConectado(usuario)){
						enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(socketConexion);
					} else { // Sino lo reconectamos
						idYPunteroAlSocket.id = usuarios->reconectar(usuario);
						idYPunteroAlSocket.punteroAlSocket = socketConexion;
						enviarMensajeDeConexionAceptadaAl(idYPunteroAlSocket.id, socketConexion);
						enviarUnMensajeAvisandoleQueYaEmpezoElJuegoAl(socketConexion);
						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
					}
				//Si el nombre de usuario no estaba registrado
				} else {
						
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

						enviarMensajeDeConexionAceptadaAl(idYPunteroAlSocket.id, socketConexion);

						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
				}

			} else {
				free(socketConexion);
			}
		} else {
			// Si se supero la cantidad maxima de usuarios enviamos un mensaje al cliente informado que ha sido rechazado

			if (*socketConexion != INVALID_SOCKET) {

				enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(socketConexion);
				Log::getInstance()->info("Se informa al cliente que se rechaza la conexion ya que se ha alcanzado el limite de usuarios.");
				vectorSockets.push_back(socketConexion);

			}else{
				free(socketConexion);
			}
		}
	}while(!seDebeCerrarElServidor);

	for_each (vectorHilos.begin(), vectorHilos.end(), waitThread);
	for_each (vectorSockets.begin(), vectorSockets.end(), freeSockets);

	return 0;
}

int MainServidor::consola(void*){
	
	char entradaTeclado[20];
	
	do {
		scanf("%s", entradaTeclado);
	} while(strcmp(entradaTeclado,"cerrar"));
	
	seDebeCerrarElServidor = true;

	//cuando cierro la conexion del socketDeEscucha, se crea igual un hilo, no controlo eso.
	closesocket(socketDeEscucha);
	return 0;
}


/*-------- Funciones publicas --------*/

int MainServidor::mainPrincipal(){

	Log::getInstance()->debug("Servidor - Main Principal");
	mutColaPrincipal = SDL_CreateMutex();
	mutLogger= SDL_CreateMutex();
	mutColaDeUsuario = new SDL_mutex*[usuarios->getCantidadMaximaDeUsuarios()];
	for(int i = 0; i < usuarios->getCantidadMaximaDeUsuarios(); i++){
		mutColaDeUsuario[i] = SDL_CreateMutex();
	}
	MensajeConId* mensajeConId;

	printf("\nEscriba 'cerrar' si desea cerrar el servidor\n"); 

	SDL_Thread* receptor = SDL_CreateThread(MainServidor::fun_recibirConexiones, "recibirConexiones", NULL);
	SDL_Thread* consola = SDL_CreateThread(MainServidor::fun_consola, "recibirConexiones", NULL);

	SDL_LockMutex(mutLogger);
	Log::getInstance()->debug("Servidor - Main Principal: se inician los thread recibirConexiones");
	SDL_UnlockMutex(mutLogger);

	
	std::queue<EstadoAvionXml*>* colaDeMensajesDelUsuario;
	//Este codigo conectado evita que el server empiece realmente si no estan todos conectados,
	//Y ademas manda el mensaje de reconexion
	bool seHaIniciadoLaPartida = false;
	while(!seDebeCerrarElServidor && !seHaIniciadoLaPartida){
		
		//Cuando estoy lleno, le aviso a todos los jugadores que la partida comienza
		if(!usuarios->puedoTenerMasUsuarios()){
			for(int i = 0; i < usuarios->cantidadDeUsuarios(); i++){
				SDL_LockMutex(mutColaDeUsuario[i]);
				colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
				colaDeMensajesDelUsuario->push(new EstadoAvionXml(-1,0,0,0));
				SDL_UnlockMutex(mutColaDeUsuario[i]);
			}
			seHaIniciadoLaPartida = true;
		}
		SDL_Delay(100);
	}

	while(!seDebeCerrarElServidor) {

		
		SDL_LockMutex(mutColaPrincipal);
		if(!colaDeMensaje.empty()) {
			

			mensajeConId = colaDeMensaje.front();
			colaDeMensaje.pop();

			SDL_UnlockMutex(mutColaPrincipal);
			//Una vez sacado el elemento de la cola principal, podemos dejar que los demás threads usen normalmente.

			/* no me interesa ahora revisar esto, es demasiada informacion en el log
			printf("Recibido del usuario:%i", mensajeConId->id);
			printf(" Movimiento id: %d frame: %d x: %d y: %d\n",mensajeConId->estadoAvionXml.getId(), mensajeConId->estadoAvionXml.getFrame(), mensajeConId->estadoAvionXml.getPosX(), mensajeConId->estadoAvionXml.getPosY());

			stringstream mensajeLog; 
			mensajeLog << "Usuario " << mensajeConId->id << " Movimiento: id: " << mensajeConId->estadoAvionXml.getId() << " frame: " <<  mensajeConId->estadoAvionXml.getFrame() << " x: " << mensajeConId->estadoAvionXml.getPosX() << " y: " << mensajeConId->estadoAvionXml.getPosY();
			mensajeLog << " SizeBytes:" << mensajeConId->estadoAvionXml.getSizeBytes();

			SDL_LockMutex(mutLogger);
			Log::getInstance()->debug(mensajeLog.str());
			SDL_UnlockMutex(mutLogger);
			*/

			//Para todos los usuarios
			for (int i = 0; i < usuarios->getCantidadMaximaDeUsuarios(); i++) {
				//Si el mensaje no vino del usuario i
				//Si el usuario i esta conectado
				
				if(i != mensajeConId->id && usuarios->estaConectado(i)){
					SDL_LockMutex(mutColaDeUsuario[i]);
					colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
					EstadoAvionXml* mensajeDeRespuesta = new EstadoAvionXml(mensajeConId->estadoAvionXml.getId(), mensajeConId->estadoAvionXml.getFrame(), mensajeConId->estadoAvionXml.getPosX(), mensajeConId->estadoAvionXml.getPosY());

					std::list<EstadoProyectilXml*>::iterator it;
					std::list<EstadoProyectilXml*> listaP = mensajeConId->estadoAvionXml.getEstadosProyectiles();

					for (it = listaP.begin(); it != listaP.end(); it++) {
						mensajeDeRespuesta->agregarEstadoProyectil(new EstadoProyectilXml((*it)->getFrame(),(*it)->getPosX(), (*it)->getPosY()));
					}
					colaDeMensajesDelUsuario->push(mensajeDeRespuesta);
					SDL_UnlockMutex(mutColaDeUsuario[i]);
				}
			}
			
			delete mensajeConId;
			//Si la cola estaba vacía, le permito a los demas threads usarla
		}else{
			SDL_UnlockMutex(mutColaPrincipal);
		}
	}

	Log::getInstance()->info("Se solicito la detención del Server.");

	SDL_WaitThread(receptor, NULL);
	SDL_WaitThread(consola, NULL);

	Log::getInstance()->debug("Servidor - Main Principal: esperando que los threads finalicen.");

	for(int i = 0; i < usuarios->getCantidadMaximaDeUsuarios(); i++){
		SDL_DestroyMutex(mutColaDeUsuario[i]);
	}
	delete mutColaDeUsuario;
	//SDL_DestroyMutex(mutColaDeUsuario[i]);
	SDL_DestroyMutex(mutColaPrincipal);
	SDL_DestroyMutex(mutLogger);

	Log::getInstance()->debug("Servidor - Main Principal: se liberaron los recursos.");
	SDL_Delay(2000);
	return 0;
}