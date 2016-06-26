#include "MainServidor.h"
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
	// luego de usarlo se debe borrar
	if (servidorXml != NULL){
		delete servidorXml;
		servidorXml = NULL;
	}

}
MainServidor* MainServidor::getInstance(){
	if(single==NULL){
		single = new MainServidor();
		return single;
	}
	else{
		return single;
	}
}

int MainServidor::parsearXML(int argc, char* argv[]) {

	ParserXml parserx;
	parserx.cargarXmlServidor(argc,argv);
	int res = parserx.validarXmlArchivoServidor();
	if (res < 0){
		printf("\nERROR: Error semantico\n");
		parserx.cargarXmlServidor(0,argv);
	}

	//luego de la carga crea los datos a partir del XML
	this->servidorXml = parserx.createDataServidorXml(); //luego de la carga crea los datos a partir del XML
	int cantidadDeClientesMaxima = servidorXml->getCantidadMaximaClientes();
	this->puerto = servidorXml->getPuerto();

	return cantidadDeClientesMaxima;
}

void MainServidor::recargarServidorXml() {
	//al reiniciar debe liberar la memoria del servidorXml
	if (this->servidorXml != NULL){
		this->servidorXml = NULL;
	}
	int cantidadDeClientesMaxima = parsearXML(this->argc, this->argv);
}

void MainServidor::parsearArchivoXml(int argc, char* argv[]){
	
	this->argc = argc;
	this->argv = argv;

	int cantidadDeClientesMaxima = parsearXML(argc, argv);

	this->usuarios = new AsignadorDeUsuarios(cantidadDeClientesMaxima);
	this->seDebeCerrarElServidor = false;
}

/*-------- Funciones de destrucción de Threads y Sockects --------*/
void freeSocketsSDL (SOCKET* s) {
	Log::getInstance()->debug("Liberando recursos del socket.");
	free(s);
}
void waitThreadSDL (SDL_Thread* h) {
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
	return instan->waitTeclasConsola(punteroAlSocketRecibido);
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
void MainServidor::escucharSocket(SOCKET sock){
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
	EstadoJuego* stJuego;
	bool* seCerroLaConexionPointer = structRecibido.seCerroLaConexion;
	std::queue<EstadoJuego*>* colaDeMensajesParaEnviar = usuarios->obtenerColaDeUsuario(id);
	printf("Se esta preparando para enviar mensajes al usuario: %i\n",id);
	//-----------------------------
	while(!(*seCerroLaConexionPointer)){
	// enviar el inicio del juego a todos los clientes
		SDL_LockMutex(mutColaDeUsuario[id]);
		if(!colaDeMensajesParaEnviar->empty()){
			stJuego = colaDeMensajesParaEnviar->front();
			colaDeMensajesParaEnviar->pop();
			SDL_UnlockMutex(mutColaDeUsuario[id]);
			char buffEnvio[MAX_BUFFER];
			int sizeEnvio = Protocolo::codificar(*stJuego,buffEnvio);

			//Fuera de uso, no hay reinicios por ahora
			/*
			if(indicaUnReinicioDelMapa(stAvionXml)) {
				//para esta operacion de reinicion no debe ejecutarse en forma simultanea
				SDL_LockMutex(mutColaDeUsuario[id]);
				recargarServidorXml();
				SDL_UnlockMutex(mutColaDeUsuario[id]);
				sizeEnvio += Protocolo::codificar(*(this->servidorXml), buffEnvio + sizeEnvio);
			}*/
			delete stJuego;
			MensajeSeguro::enviar(socket, buffEnvio, sizeEnvio);

		}else{//Si la cola estaba vacía, permito que los demas threads usen la cola
			SDL_UnlockMutex(mutColaDeUsuario[id]);
		}
	}
	return 0;
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
bool MainServidor::isHayBytes(int sizeBytesIn){
	return(sizeBytesIn > 0);
}

void MainServidor::actualizarLaUltimaPosicionDelUsuario(int id, EstadoAvion* estadoAvion){
	Posicion posicion;
	posicion.setPosX(estadoAvion->getPosX());
	posicion.setPosY(estadoAvion->getPosY());
	usuarios->setPosicionAUsuario(id, posicion);
}

int MainServidor::atenderCliente(void* idYPunteroAlSocketRecibido) {	
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
	int sizeBytesIn = 1;
	structParaEnviar->idYPunteroAlSocket = idYPunteroAlSocket;
	structParaEnviar->seCerroLaConexion = seCerroLaConexion;
	threadDeEnvioDeMensajes = SDL_CreateThread(MainServidor::fun_revisarSiHayMensajesParaElClienteYEnviarlos, "mensajesParaElCliente", (void*) structParaEnviar);	
	while (isHayBytes(sizeBytesIn) && !seDebeCerrarElServidor){ //mientras estemos conectados con el otro pc
		Evento* eventoRecibido;
		MensajeConIdRecibido* mensajeParaLaColaPrincipal;
		sizeBytesIn = MensajeSeguro::recibir(socket,bufferEntrada);
		if (isHayBytes(sizeBytesIn)){
			//Por temas de lecturas pongo una id de evento 0, luego en el decodificar ira la que corresponde
			mensajeParaLaColaPrincipal = new MensajeConIdRecibido;
			eventoRecibido = new Evento(0);
			Protocolo::decodificar(bufferEntrada,eventoRecibido);
			SDL_LockMutex(mutColaPrincipal);
			mensajeParaLaColaPrincipal->id = id;
			mensajeParaLaColaPrincipal->evento = eventoRecibido;
			colaDeMensaje.push(mensajeParaLaColaPrincipal);
			SDL_UnlockMutex(mutColaPrincipal);
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
	printf("\nLa cantidad de clientes conectados es: %i\n",usuarios->cantidadDeUsuarios());
	SDL_LockMutex(mutLogger);
	Log::getInstance()->info("La cantidad de clientes conectados es: " + usuarios->cantidadDeUsuarios());
	SDL_UnlockMutex(mutLogger);
	return 0;
}
	

void MainServidor::enviarModeloXmlxConexionAceptadaAl(int idCliente, SOCKET* socket){
	// Mensaje de conexion exitosa
	char buffEnvio[MAX_BUFFER];
	int offset = 0;
	MensajeXml mensajeEnvio;
	mensajeEnvio.setValor(MSJ_CONEX_ACEPT, strlen(MSJ_CONEX_ACEPT));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	offset = Protocolo::codificar(mensajeEnvio,buffEnvio + offset);
	// Modo de Juego
	MensajeXml mensajeModoDeJuego;
	char* modoDeJuego = ConfiguracionInicialJuego::getInstance()->getModoDeJuego();
	mensajeModoDeJuego.setValor(modoDeJuego, strlen(modoDeJuego));
	mensajeModoDeJuego.setTipo(TIPO_STRING);
	mensajeModoDeJuego.calculateSizeBytes();
	offset += Protocolo::codificar(mensajeModoDeJuego,buffEnvio + offset);
	// Depenediendo del modo de juego se envia la disponibilidad de los equipos
	if (strcmp(modoDeJuego, MODO_EQUIPO) == 0) {
		MensajeXml mensajeDisponibilidad;
		char* disponibilidad = ConfiguracionInicialJuego::getInstance()->getDisponibilidad();
		mensajeDisponibilidad.setValor(disponibilidad, strlen(disponibilidad));
		mensajeDisponibilidad.setTipo(TIPO_STRING);
		mensajeDisponibilidad.calculateSizeBytes();
		offset += Protocolo::codificar(mensajeDisponibilidad,buffEnvio + offset);
	}
	// ID del usuario
	string idString = StringUtil::intToString(idCliente);
	mensajeEnvio.setValor((char*)idString.c_str(), strlen(idString.c_str()));
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	offset += Protocolo::codificar(mensajeEnvio,buffEnvio + offset);
	// Posicion de inicio del avión
	Posicion* pos;
	Posicion posAEnviar;
	pos = usuarios->getPosicionDeUsuario(idCliente);
	posAEnviar.setPosX(pos->getPosX());
	posAEnviar.setPosY(pos->getPosY());
	posAEnviar.calculateSizeBytes();
	offset += Protocolo::codificar(posAEnviar, buffEnvio + offset);

	//NOTA POS ENTREGA 2: el tema de las posiciones del mapa es algo que se vera revisado
	//Lo relacionado con eso y la reconexion, es algo que cambiara
	//Estas lineas de codigo no estan totalmente en uso

	//Si no tengo una posicion del mapa que sirva, pido una
	Posicion posDelMapa;
	//Si estoy solo yo conectado, no puedo pedirle la posicion del mapa a ningun cliente, asi que
	//La pongo en 0
	if(usuarios->cantidadDeUsuarios() == 1 && !seActualizoLaUltimaPosicionDelMapa){
		posicionDelMapa = 0;
	}
	//Espero a tener una posicion del mapa en el juego actual
	//Si la posicion del mapa ya se uso, ya no sirve para otro cliente, asi que pongo que no esta actualizada
	//Codifico la posicion y la envio
	posDelMapa.setPosX(0);
	posDelMapa.setPosY(posicionDelMapa);
	posDelMapa.calculateSizeBytes();
	offset += Protocolo::codificar(posDelMapa, buffEnvio + offset);

	// XML de configuracion
	offset += Protocolo::codificar(*this->servidorXml,buffEnvio + offset);
	MensajeSeguro::enviar(*socket, buffEnvio, offset);
}

/**
 * crea un MensajeXml temporalmente que luego enviar por un socket
 * @param  socket socket del cliente al que se enviara el mensajeXML
 * @param mensajeStr cadena de texto que contiene el mensaje a enviar
 */
void MainServidor::sendMensajeXml(SOCKET* socket,char * mensajeStr){
	char buffEnvio[MAX_BUFFER];
	MensajeXml mensajeEnvio;
	mensajeEnvio.setValor(mensajeStr,strlen(mensajeStr));;
	mensajeEnvio.setTipo(TIPO_STRING);
	mensajeEnvio.calculateSizeBytes();
	int sizeEnvio = Protocolo::codificar(mensajeEnvio,buffEnvio);
	MensajeSeguro::enviar(*socket, buffEnvio, sizeEnvio);
}
/**
 * recibe un MensajeXml creado fuera del metodo y luego lo carga con datos
 * obtenidos desde el socket
 * @param socket socket del cliente sobre el que se recibe el mensajeXML
 * @param mensajeRecib MensajeXml que contiene la salida cargada desde el socket
 */
void MainServidor::receiveMensajeXml(SOCKET* socket,MensajeXml * mensajeRecib){
	char bufferEntrada[MAX_BUFFER];
	MensajeSeguro::recibir(*socket, bufferEntrada);
	int sizeRecib = Protocolo::decodificar(bufferEntrada, mensajeRecib);
}

void MainServidor::enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket){
	sendMensajeXml(socket,MSJ_SUPERO_MAX);
}

void MainServidor::enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(SOCKET* socket){
	sendMensajeXml(socket,MSJ_USR_YA_CONECT);
}
/**
 * este metodo envia el estado INICIAL del juego/de la partida
 * @param socket socket del cliente usado para enviar el estado del avion
 */
void MainServidor::sendEstadoAvionJuegoIniciado(SOCKET* socket){
	char buffEnvio[MAX_BUFFER];
	//indica el estado inicial de la partida
	EstadoAvion estadoAvionXmlInicial(-1,0,0,0,0);
	estadoAvionXmlInicial.calculateSizeBytes();
	int sizeEnvio = Protocolo::codificar(estadoAvionXmlInicial, buffEnvio);
	MensajeSeguro::enviar(*socket, buffEnvio, sizeEnvio);
}

int MainServidor::recibirConexiones(void*){
	struct sockaddr_in local;
	SOCKET* socketConexion;
	int len = sizeof(struct sockaddr);
	IdYPunteroAlSocket idYPunteroAlSocket;
	socketDeEscucha = obtenerSocketInicializado(local);
	escucharSocket(socketDeEscucha);
	Log::getInstance()->debug("En espera de conexiones");
	printf("En espera de conexiones\n");
	printf("[Cuando se vaya recibiendo texto aparecera en pantalla]\n");

	do{
		socketConexion=(SOCKET*)malloc(sizeof(SOCKET)); // se usa malloc porque de otra forma siempre usas el mismo socket
		*socketConexion=accept(socketDeEscucha,(sockaddr*)&local,&len);
		if(!usuarios->elServidorEstaLleno()){
			if (*socketConexion != INVALID_SOCKET) {
				printf("Nueva conexion aceptada\n");
				Log::getInstance()->info("Nueva conexion acceptada");
				// Antes de crear un usuario realizo las validaciones de nombre de usuario
				MensajeXml mensajeUsuario;
				receiveMensajeXml(socketConexion,&mensajeUsuario);
				char* usuario = mensajeUsuario.getValor();

				// Si ese nombre de usuario existe
				if(usuarios->isNombreUsuarioExistente(usuario)){
					// Si ya esta conectado lo rechazo
					if(usuarios->estaConectado(usuario)){
						enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(socketConexion);
					} else { // Sino lo reconectamos
						idYPunteroAlSocket.id = usuarios->reconectar(usuario);
						idYPunteroAlSocket.punteroAlSocket = socketConexion;
						enviarModeloXmlxConexionAceptadaAl(idYPunteroAlSocket.id, socketConexion);
						// Verifico si se juega por equipos
						if (ConfiguracionInicialJuego::getInstance()->seJuegaPorEquipos()) {
							// Recibe en qué equipo se conectó si es que había disponibilidad
							if (ConfiguracionInicialJuego::getInstance()->hayDisponibilidad()) {
								MensajeXml mensajeEquipo;
								receiveMensajeXml(socketConexion, &mensajeEquipo);
								char* equipo = mensajeEquipo.getValor();
								ConfiguracionInicialJuego::getInstance()->asociarUsuarioAEquipo(idYPunteroAlSocket.id, equipo);
							}
							else {
								ConfiguracionInicialJuego::getInstance()->agregarUsuario(idYPunteroAlSocket.id);
							}
						}
						else {
							ConfiguracionInicialJuego::getInstance()->agregarUsuario(idYPunteroAlSocket.id);
						}
						sendEstadoAvionJuegoIniciado(socketConexion);
						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
					}
				//Si el nombre de usuario no estaba registrado y puedo tener mas usuarios, creo uno
				} else if(usuarios->puedoTenerUsuariosNuevos()) {
						idYPunteroAlSocket.id = usuarios->crearUsuarioYObtenerId(usuario);
						idYPunteroAlSocket.punteroAlSocket = socketConexion;
						printf("La cantidad de clientes conectados es: %d\n",usuarios->cantidadDeUsuarios());
						printf("La id del nuevo usuario es: %d\n",idYPunteroAlSocket.id);
						if(!usuarios->elServidorEstaLleno()){
							printf("Todavia se pueden tener mas usuarios\n");
						}else{
							printf("Se ha alcanzado el limite de usuarios");
							Log::getInstance()->info("Se ha alcanzado el limite de usuarios.");
						}
						enviarModeloXmlxConexionAceptadaAl(idYPunteroAlSocket.id, socketConexion);
						// Verifico si se juega por equipos
						if (ConfiguracionInicialJuego::getInstance()->seJuegaPorEquipos()) {
							// Recibe en qué equipo se conectó si es que había disponibilidad
							if (ConfiguracionInicialJuego::getInstance()->hayDisponibilidad()) {
								MensajeXml mensajeEquipo;
								receiveMensajeXml(socketConexion, &mensajeEquipo);
								char* equipo = mensajeEquipo.getValor();
								ConfiguracionInicialJuego::getInstance()->asociarUsuarioAEquipo(idYPunteroAlSocket.id, equipo);
							}
							else {
								ConfiguracionInicialJuego::getInstance()->agregarUsuario(idYPunteroAlSocket.id);
							}
						}
						else {
							ConfiguracionInicialJuego::getInstance()->agregarUsuario(idYPunteroAlSocket.id);
						}
						vectorHilos.push_back(SDL_CreateThread(MainServidor::fun_atenderCliente, "atenderAlCliente", (void*) &idYPunteroAlSocket));
						vectorSockets.push_back(socketConexion);
				}else if(!usuarios->puedoTenerUsuariosNuevos()){
					//Este no es el mensaje adecuado, habria que poner un mensaje del estilo
					//La partida esta llena
					enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(socketConexion);
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
	for_each (vectorHilos.begin(), vectorHilos.end(), waitThreadSDL);
	for_each (vectorSockets.begin(), vectorSockets.end(), freeSocketsSDL);
	return 0;
}
int MainServidor::waitTeclasConsola(void*){
	char entradaTeclado[20];

	do {
		scanf("%s", entradaTeclado);
	} while(strcmp(entradaTeclado,"cerrar"));

	seDebeCerrarElServidor = true;
	//cuando cierro la conexion del socketDeEscucha, se crea igual un hilo, no controlo eso.
	closesocket(this->socketDeEscucha);
	return 0;
}

void MainServidor::esperarAQueTodosLosUsuariosEstenConectadosParaContinuar(){
	bool seHaIniciadoLaPartida = false;
	while(!seDebeCerrarElServidor && !seHaIniciadoLaPartida){
		if(usuarios->elServidorEstaLleno())
			seHaIniciadoLaPartida = true;
		SDL_Delay(100);
	}
}

void MainServidor::avisarATodosLosUsuariosQueComenzoLaPartida(){
	std::queue<EstadoJuego*>* colaDeMensajesDelUsuario;
	Evento evento(comienzaLaPartida);
	for(int i = 0; i < usuarios->cantidadDeUsuarios(); i++){
		SDL_LockMutex(mutColaDeUsuario[i]);
		colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
		EstadoJuego* estadoJuego = new EstadoJuego(evento);
		colaDeMensajesDelUsuario->push(estadoJuego);
		SDL_UnlockMutex(mutColaDeUsuario[i]);
	}
}

void MainServidor::comunicarEventosRecibidosAlJuego(){	
	MensajeConIdRecibido* mensajeConIdRecibido;

	SDL_LockMutex(mutColaPrincipal);

		while(!colaDeMensaje.empty()) {
			mensajeConIdRecibido = colaDeMensaje.front();
			colaDeMensaje.pop();
			modeloJuego->actualizarElJuegoEnBaseA(mensajeConIdRecibido->evento, mensajeConIdRecibido->id);
			delete mensajeConIdRecibido;
		}

	SDL_UnlockMutex(mutColaPrincipal);
}

void MainServidor::comunicarElNuevoEstadoDelJuegoALosClientes(){
	std::queue<EstadoJuego*>* colaDeMensajesDelUsuario;
	EstadoJuego* estadoJuego;
	
	//Para todos los usuarios
	for (int i = 0; i < usuarios->getCantidadMaximaDeUsuarios(); i++) {
		//Si el usuario i esta conectado
		if(usuarios->estaConectado(i)){
			SDL_LockMutex(mutColaDeUsuario[i]);
			//Cada llamada de obtener, da uno nuevo, luego cuando se saca de una de las colas
			//Se llama al delete
			colaDeMensajesDelUsuario = usuarios->obtenerColaDeUsuario(i);
			estadoJuego = modeloJuego->obtenerEstadoDelJuego();
			colaDeMensajesDelUsuario->push(estadoJuego);
			SDL_UnlockMutex(mutColaDeUsuario[i]);
		}
	}
}
/*-------- Funciones publicas --------*/
int MainServidor::mainPrincipal(){
	Log::getInstance()->debug("Servidor - Main Principal");
	mutColaPrincipal = SDL_CreateMutex();
	mutLogger= SDL_CreateMutex();
	mutColaDeUsuario = new SDL_mutex*[usuarios->getCantidadMaximaDeUsuarios()];
	posicionDelMapa = 0;
	for(int i = 0; i < usuarios->getCantidadMaximaDeUsuarios(); i++){
		mutColaDeUsuario[i] = SDL_CreateMutex();
	}
	printf("\nEscriba 'cerrar' si desea cerrar el servidor\n");

	// Configura la etapa anterior al juego sobre cómo se organizan los jugadores dependiendo del modo del juego
	ConfiguracionInicialJuego::getInstance()->inicializar(this->servidorXml);

	SDL_Thread* receptor = SDL_CreateThread(MainServidor::fun_recibirConexiones, "recibirConexiones", NULL);
	SDL_Thread* consola = SDL_CreateThread(MainServidor::fun_consola, "recibirConexiones", NULL);
	SDL_LockMutex(mutLogger);
	Log::getInstance()->debug("Servidor - Main Principal: se inician los thread recibirConexiones");
	SDL_UnlockMutex(mutLogger);

	esperarAQueTodosLosUsuariosEstenConectadosParaContinuar();

	modeloJuego = new ModeloDelJuego(servidorXml, usuarios->getCantidadMaximaDeUsuarios());

	avisarATodosLosUsuariosQueComenzoLaPartida();

	//Bucle principal
	while(!seDebeCerrarElServidor) {

		comunicarEventosRecibidosAlJuego();
		modeloJuego->actualizarMovimientos();
		//Por ahora comuncia estado aviones, deberia comunicar un estadoJuego
		comunicarElNuevoEstadoDelJuegoALosClientes();
		
		//Sin el delay el server va mucho mas rapido que lo que grafica el cliente
		//Y el avion se teletransporta de una punta a la otra
		SDL_Delay(10);
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