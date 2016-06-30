#include "MainCliente.h"

MainCliente* MainCliente::single = NULL;

bool MainCliente::serverDesconectado = true;
bool MainCliente::cerrarConexion = true;

MainCliente* MainCliente::getInstance(){
	if(single == NULL){
		single = new MainCliente();
		return single;
	}
	else{
		return single;
	}
}

MainCliente::MainCliente(){
	this->conectado = false;
	// aca deberia de obtener el ip, port y cargar los mensajes en el map
	this->ip = "";
	this->port = -1;
	this->parserx = new ParserXml();
	this->servidorXml = new ServidorXml();
}

MainCliente::~MainCliente(){
	delete this->parserx;
	if (this->servidorXml != NULL)
		delete this->servidorXml;
}

void MainCliente::liberar(){
	Log::liberar();
	delete single;
}

// Ahora se carga la IP y el Puerto por consola, se deja esta función para configuraciones del cliente
void MainCliente::parsearArchivoXml(int argc, char* argv[]){
	getParserXml()->cargarXmlCliente(argc,argv);
	int res = getParserXml()->validarXmlArchivoCliente();
	if (res < 0){
		printf("\nERROR: Error semantico\n");
		Log::getInstance()->error("ERROR: Error semantico.");
		getParserXml()->cargarXmlCliente(0,argv);
	}
	//luego de la carga crea los datos a partir del XML
	ClienteXml * clienteXml = getParserXml()->createDataClienteXml();
	//se cargan los datos desde el cliente
	//copia la ip
	this->ip.assign(clienteXml->getConexionXmlCopy()->getIp());
	//copia el puerto
	int puerto = clienteXml->getConexionXmlCopy()->getPuerto();
	char cadena[10];
	sprintf(cadena,"%d",puerto);
	this->port.assign(cadena);
	// luego de usarlo se debe borrar
	delete clienteXml;
}

ParserXml * MainCliente::getParserXml(){
	return this->parserx;
}

int MainCliente::chequearConexion(int len){
	if (len == 0){
		printf("\n No llego el mensaje, se desconecto el servidor\n");
		conectado=false;
		return -1;
	}
	else if (len < 0){
		conectado=false;
		int error = WSAGetLastError();

		if(error == WSAENOTCONN || error == WSAECONNRESET)
			printf("\n Se a desconectado inesperadamente el servidor\n");
		else if (error == WSAENETDOWN)
			printf("\nRed caida\n");
		else
			printf("\nError en conexion con el servidor\n");
		return -1;
	}

	return 0;
}

int MainCliente::inicializarConexion(){

	//Inicializamos
	WSAStartup(MAKEWORD(2,2),&wsa);

	//resolvemos el nombre de dominio localhost, esto se resolverá a 127.0.0.1
	host=gethostbyname(ip.c_str());

	//creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock==-1)
	{
		Log::getInstance()->error(" al crear el socket.");
		printf("Error al crear el socket");
		return -1;
	}
	int c;
	setsockopt (sock, IPPROTO_TCP, SO_REUSEADDR | SOCK_STREAM, (char*)&c, sizeof(int));
	//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
	//y decimos que el puerto al que deberá conectar es el 9999 con el protocolo ipv4
	direc.sin_family=AF_INET;
	direc.sin_port=htons(atoi(port.c_str()));
	direc.sin_addr = *((struct in_addr *)host->h_addr);
	memset(direc.sin_zero,0,8);

	return 0;
}
void MainCliente::grabarEnElLogLaDesconexion(int len){
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

int MainCliente::fun_recibirMensajes(void* ptrSock) {
	return MainCliente::getInstance()->recibirMensajes(ptrSock);
}

int MainCliente::recibirMensajes(void* ptrSock){
	bool primerMensaje =true;
	char bufferEntrada[MAX_BUFFER];
	while (!cerrarConexion && !serverDesconectado){
		int len=MensajeSeguro::recibir(*((SOCKET*)ptrSock),bufferEntrada); //recibimos los datos que envie
		if (len>0){
			// espero el mensaje del server, comenzar el juego para desbloquear SDL
			EstadoJuego* stJuego = NULL;
			if(primerMensaje){
				// en realidad no necesito chequear el mensaje
				int offset = Protocolo::decodificar(bufferEntrada,stJuego);
				if (stJuego->obtenerEvento()->getNumeroDeEvento() == comienzaLaPartida){
					// Si el server nos envia respuesta que debemos iniciar el juego
					Log::getInstance()->info("Comenzar el juego");
					cout<<"Comenzar el juego"<<endl;
					VistaJuego::getInstance()->setJugar();
					primerMensaje=false;
					delete stJuego;
				}
			} else {
				//si seguimos conectados
				int offset = Protocolo::decodificar(bufferEntrada,stJuego);
				VistaJuego::getInstance()->actualizarEstadoJuego(stJuego);
				//Un mensaje con id -2 indica que se reinicio el mapa
				/*
				if(stAvion->getId() == -2){
					//se debe recrear el servidor pues el anterior ya no sirve
					recreateServidorXml();
					Protocolo::decodificar(bufferEntrada + offset, this->servidorXml);
					VistaJuego::getInstance()->reiniciar(this->servidorXml, 0);
				}*/
			}
		}
		else{
			grabarEnElLogLaDesconexion(len);
			serverDesconectado = true;
		}
	}
	return 0;
}

int MainCliente::conectarYEjecutar(){
	//----------------------CONECTAR-BEGIN------------------
#ifdef FAKE_DEBUG_CLIENTE
	VistaJuego::getInstance()->getJugador()->nombreDeUsuario.assign("Cliente-A");
#else
	VistaJuego * visJue = VistaJuego::getInstance();
	VistaInicio * visIni = VistaInicio::getInstance();
	this->ip = visIni->getIP();
	this->port = visIni->getPuerto();
	visJue->getJugador()->nombreDeUsuario.assign(visIni->getUsuario());
#endif
	inicializarConexion();

	if(conectado == true){
		Log::getInstance()->warn(" el cliente ya se encuentra conectado.");
		printf("ya se encuentra conectado \n");
	}
	else{
		//Intentamos establecer la conexión
		int conex=connect(sock,(sockaddr *)&direc, sizeof(sockaddr));
		if (conex==-1) //si no se ha podido conectar porque no se ha encontrado el host o no está el puerto abierto
		{
			Log::getInstance()->error(" no se ha podido conectar.");
			printf("No se ha podido conectar\n");
			printf("%i", conex);
			return -1;
		}
		else{
			// Se envia un mensaje al servidor para que valide el nombre de usuario
			MensajeXml mensajeUsuario;
			mensajeUsuario.setValor((char*)VistaJuego::getInstance()->getJugador()->nombreDeUsuario.c_str(), strlen(VistaJuego::getInstance()->getJugador()->nombreDeUsuario.c_str()));
			mensajeUsuario.setTipo(TIPO_STRING);
			mensajeUsuario.calculateSizeBytes();
			char bufferSalida [MAX_BUFFER];
			int size = Protocolo::codificar(mensajeUsuario, bufferSalida);
			MensajeSeguro::enviar(sock, bufferSalida, size);

			char bufferEntrada[MAX_BUFFER];
			// Se recibe la confirmación de la validación del nombre de usuario
			int len2 = MensajeSeguro::recibir(sock,bufferEntrada);
			if (len2 <= 0){// Es un error
				chequearConexion(len2);
			}
			else{
				//decodificar el mensaje
				MensajeXml mensaXmlRespuestaUsuario;
				int offset = Protocolo::decodificar(bufferEntrada,&mensaXmlRespuestaUsuario);
				char * respuesta = mensaXmlRespuestaUsuario.getValor();
				if (strcmp(respuesta,MSJ_CONEX_ACEPT) == 0){
					//VistaInicio::getInstance()->close();
					char* idUsuario;
					Posicion posicion;
					Posicion posicionMapa;
					// Si el server nos envia respuesta, es que la conexion ha sido satisfactoria
					Log::getInstance()->info("El cliente se ha conectado correctamente.");
					conectado = true;
					MainCliente::serverDesconectado = false;
					MainCliente::cerrarConexion = false;

					// Decodifica cómo se juega
					MensajeXml mensaXmlModoDeJuego;
					offset += Protocolo::decodificar(bufferEntrada + offset,&mensaXmlModoDeJuego);
					char * modoDeJuego = mensaXmlModoDeJuego.getValor();

					if (strcmp(modoDeJuego, MODO_EQUIPO) == 0) {
						// Decodifica si hay equipos libres
						MensajeXml mensaXmlDisponibilidadEquipos;
						offset += Protocolo::decodificar(bufferEntrada + offset,&mensaXmlDisponibilidadEquipos);
						char * disponibilidadEquipos = mensaXmlDisponibilidadEquipos.getValor();

						if (strcmp(disponibilidadEquipos, HAY_DISPONIBILIDAD) == 0) {
							VistaInicio::getInstance()->mostrarSeleccionDeEquipos();
							string equipo = VistaInicio::getInstance()->getEquipo();

							// Envio qué equipo se seleccionó
							MensajeXml mensajeEquipo;
							mensajeEquipo.setValor((char*)equipo.c_str(), strlen(equipo.c_str()));
							mensajeEquipo.setTipo(TIPO_STRING);
							mensajeEquipo.calculateSizeBytes();
							char bufferSalida [MAX_BUFFER];
							int size = Protocolo::codificar(mensajeEquipo, bufferSalida);
							MensajeSeguro::enviar(sock, bufferSalida, size);
						}

						MensajeXml mensaXml;

						offset += Protocolo::decodificar(bufferEntrada + offset,&mensaXml);

						char* idUsuarioXml = mensaXml.getValor();

						idUsuario= new char[strlen(idUsuarioXml) + 1];
						std::copy(idUsuarioXml, idUsuarioXml + strlen(idUsuarioXml), idUsuario);

						// Se decodifica la posicion inicial desde donde arranca el avión
						offset += Protocolo::decodificar(bufferEntrada + offset, &posicion);

						// Se decodifica la posicion del mapa, que tiene solo una componente: Y
						offset += Protocolo::decodificar(bufferEntrada + offset, &posicionMapa);

						//se procede a decodificar el resto del mensaje
						//se decodifica el escenario completo
						offset += Protocolo::decodificar(bufferEntrada + offset,this->servidorXml);
					}
					else {
						// Se juega sin equipos
						MensajeXml mensaXml;
						offset += Protocolo::decodificar(bufferEntrada + offset,&mensaXml);

						char* idUsuarioXml = mensaXml.getValor();
						idUsuario= new char[strlen(idUsuarioXml) + 1];
						std::copy(idUsuarioXml, idUsuarioXml + strlen(idUsuarioXml), idUsuario);

						// Se decodifica la posicion inicial desde donde arranca el avión
						offset += Protocolo::decodificar(bufferEntrada + offset, &posicion);

						// Se decodifica la posicion del mapa, que tiene solo una componente: Y
						offset += Protocolo::decodificar(bufferEntrada + offset, &posicionMapa);

						//se procede a decodificar el resto del mensaje
						//se decodifica el escenario completo
						offset += Protocolo::decodificar(bufferEntrada + offset,this->servidorXml);
					}

					// Se cierra la ventana del menu de inicio
					VistaInicio::getInstance()->close();
					// Creo un hilo para escuchar los mensajes
					receptor=SDL_CreateThread(fun_recibirMensajes, "recibirMensajes", &sock);
	//----------------------CONECTAR-END------------------
					VistaJuego *visJuego = VistaJuego::getInstance();
					visJuego->getJugador()->nombreDeUsuario.assign(VistaInicio::getInstance()->getUsuario());
					visJuego->getJugador()->setIdCliente(atoi(idUsuario));
					visJuego->getJugador()->setPosicionAvion(posicion);

					visJuego->readServidorXml(this->servidorXml);
					visJuego->agregarObservador(this);
	//----------------------EJECUTAR-BEGIN------------------
					visJuego->inicializar();
					visJuego->ejecutar(this->servidorXml, posicionMapa.getPosY());
					// se termina el programa cuando el usuario hace click en x del SDL_window
	//----------------------EJECUTAR-END------------------
					terminarElCliente();
				}
				else if (strcmp(respuesta,MSJ_SUPERO_MAX) == 0){
					// El server envia un mensaje al superar la cantidad de clientes
					Log::getInstance()->error(bufferEntrada);
				#ifndef FAKE_DEBUG_CLIENTE
					VistaInicio::getInstance()->mostrarMensajeInformacion(MSJ_SUPERO_MAX);
				#endif
					shutdown(sock,2);
					closesocket(sock);
					terminarElCliente();
				}
				else if (strcmp(respuesta, MSJ_USR_YA_CONECT) == 0) {
					// El server ya tiene un usuario igual y está conectado
					Log::getInstance()->error(bufferEntrada);
				#ifndef FAKE_DEBUG_CLIENTE
					VistaInicio::getInstance()->mostrarMensajeInformacion(MSJ_USR_YA_CONECT);
				#endif
					desconectar();
					terminarElCliente();
				}
			}
		}
	}
	return 0;
}
int MainCliente::terminarElCliente(){

	SDL_Delay(1000);
	this->salir();
	this->opt=OPT_SALIR;
	return 0;
}
int MainCliente::desconectar(){
	shutdown(sock,2);
	closesocket(sock);
	conectado=false;
	MainCliente::cerrarConexion = false;
	return 0;
}

int MainCliente::salir(){
	mapMensajes.clear(); // chequear si se liberan los string
	// liberar la memoria de los mensajes
	desconectar();
	return 0;
}

/**
 * se encarga de liberar la memoria del servidorXML
 * y volver a alocar memoria para el nuevo servidorXML
 */
void MainCliente::recreateServidorXml(){
	if (this->servidorXml != NULL){
		delete this->servidorXml;
		this->servidorXml = new ServidorXml();
	}
}

/**
* muestra el menu y direcciona a las opciones
*/
int MainCliente::menu(){
	opt = 0;
	while (opt != OPT_SALIR){

#ifndef FAKE_DEBUG_CLIENTE
		inicio();
#endif
		conectarYEjecutar();
	}
	return 0;
}

int MainCliente::inicio() {
	VistaInicio::getInstance()->inicializar();
	VistaInicio::getInstance()->mostrar();
	return 0;
}

int MainCliente::actualizar(Evento* evento){
	char * buffEnvio = new char[MAX_BUFFER];
	int sizeBytesTotalLista = Protocolo::codificar(*evento,buffEnvio);
	int estado=0;
	if((estado=chequearConexion(MensajeSeguro::enviar(sock,buffEnvio,sizeBytesTotalLista)))<0) {
		printf("No se pudo enviar el movimiento, el cliente termina \n");
		system("PAUSE");
	}
	delete[] buffEnvio;
	delete evento;
	return estado;
}