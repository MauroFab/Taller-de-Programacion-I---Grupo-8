#include "MainCliente.h"

bool MainCliente::serverDesconectado = true;
bool MainCliente::cerrarConexion = true;

MainCliente::MainCliente(){
//	this->dirXML.assign("");
//	this->conex = 0;
//	this->len = 0;
	this->conectado = false;
	// aca deberia de obtener el ip, port y cargar los mensajes en el map
	this->ip = "";
	this->port = -1;
	// si usan el principal comentar inicializar()
	this->parserx = new ParserXml();
	this->servidorXml = new ServidorXml();

	this->nombreDeUsuario = "";
}

MainCliente::~MainCliente(){
	delete this->parserx;
	if (this->servidorXml != NULL)
		delete this->servidorXml;
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
	//else{
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
//	std::cout<< port<<std::endl;
	// luego de usarlo se debe borrar
	delete clienteXml;
	//	}
}

ParserXml * MainCliente::getParserXml(){
	return this->parserx;
}

int MainCliente::chequearConexion(int len){

	if (len == 0){
		printf("\n No llego el mensaje, se desconecto el servidor\n");
		conectado=false;
		system("PAUSE");
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
		system("PAUSE");
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

int MainCliente::recibirMensajes(void* ptrSock){
	bool primerMensaje =true;
	char bufferEntrada[MAX_BUFFER];

	while (!cerrarConexion && !serverDesconectado){ 

		int len=MensajeSeguro::recibir(*((SOCKET*)ptrSock),bufferEntrada); //recibimos los datos que envie

		if (len>0){
			// espero el mensaje del server, comenzar el juego para desbloquear SDL
			if(primerMensaje){
				// en realidad no necesito chequear el mensaje
				MensajeXml mensaXml;
				int offset = Protocolo::decodificar(bufferEntrada,&mensaXml);
				if (mensaXml.getId() == -1){
					// Si el server nos envia respuesta que debemos iniciar el juego
					Log::getInstance()->info("Comenzar el juego");
					cout<<"Comenzar el juego"<<endl;
					Juego::getInstance()->setJugar();
					primerMensaje=false;
				}
			} else {

				//si seguimos conectados
				//--------------------------------
				EstadoAvionXml * stAvionXml = new EstadoAvionXml();
				Protocolo::decodificar(bufferEntrada,stAvionXml);

				if(stAvionXml->getId() >= 0){

					EstadoAvion* estadoAvion = new EstadoAvion(stAvionXml->getId(), stAvionXml->getFrame(), stAvionXml->getPosX(), stAvionXml->getPosY());

					// Itero la lista de proyectiles y los agrego al estado avion 
					std::list<EstadoProyectilXml*>::iterator it;

					std::list<EstadoProyectilXml*> lista = stAvionXml->getEstadosProyectiles();

					for (it = lista.begin(); it != lista.end(); it++) {
						estadoAvion->agregarEstadoProyectil(new EstadoProyectil((*it)->getFrame(),(*it)->getPosX(), (*it)->getPosY()));
					}

					Juego::getInstance()->actualizarMovimientos(estadoAvion);
				}
				//Un mensaje con id -2 indica que se reinicio el mapa
				if(stAvionXml->getId() == -2){
					Mapa::getInstace()->reiniciar();
				}
				delete stAvionXml;
			}
			//--------------------------------
		}else{
			grabarEnElLogLaDesconexion(len);
			serverDesconectado = true;
		}
	}

	return 0;
}

void MainCliente::cargarIP() {

	system("CLS");

	printf("\n%s\n", "------------------------------------------------------------------------");

	printf("Ingrese IP\n");

	string ip = "";

	while (strcmp(ip.c_str(), "") == 0) {
		cin>>ip;
	}

	this->ip = ip;
}

void MainCliente::cargarPuerto() {

	system("CLS");

	printf("\n%s\n", "------------------------------------------------------------------------");

	printf("Ingrese Puerto\n");

	string puerto = "";

	while (strcmp(puerto.c_str(), "") == 0) {
		cin>>puerto;
	}

	this->port = puerto;
}

void MainCliente::cargarIpYPuerto() {

	cargarIP();
	cargarPuerto();
}

void MainCliente::cargarNombreDeUsuario() {

	system("CLS");

	printf("\n%s\n", "------------------------------------------------------------------------");

	printf("Ingrese su nombre de usuario\n");

	string nombreDeUsuario = "";

	while (strcmp(nombreDeUsuario.c_str(), "") == 0) {
		cin>>nombreDeUsuario;
	}

	this->nombreDeUsuario = nombreDeUsuario;
}


int MainCliente::conectar(){
#ifndef FAKE_DEBUG_CLIENTE	
	cargarIpYPuerto();
#endif	
	inicializarConexion(); 
#ifndef FAKE_DEBUG_CLIENTE		
	cargarNombreDeUsuario();
#else
	this->nombreDeUsuario.assign("cliente-A");
#endif	

	if(conectado == true){
		Log::getInstance()->warn(" el cliente ya se encuentra conectado.");
		printf("ya se encuentra conectado \n"); //WARN?
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
			mensajeUsuario.setValor((char*)this->nombreDeUsuario.c_str(), strlen((this->nombreDeUsuario).c_str()));
			mensajeUsuario.setTipo(TIPO_STRING);
			mensajeUsuario.calculateSizeBytes();

			char bufferSalida [MAX_BUFFER];

			int size = Protocolo::codificar(mensajeUsuario, bufferSalida);

			MensajeSeguro::enviar(sock, bufferSalida, size);

			// Se rerrcibe la confirmación de la validación del nombre de usuario

			int len2 = 2;
			char bufferEntrada[MAX_BUFFER];

			len2 = MensajeSeguro::recibir(sock,bufferEntrada);

			if (len2 <= 0){// Es un error
				chequearConexion(len2);
			}
			else{
				//decodificar el mensaje
				MensajeXml mensaXml;
				int offset = Protocolo::decodificar(bufferEntrada,&mensaXml);
				char * respuesta = mensaXml.getValor();

				if (strcmp(respuesta,FAKE_MENSAJE_01) == 0){

					// Si el server nos envia respuesta es que la conexion ha sido satisfactoria
					Log::getInstance()->info("El cliente se ha conectado correctamente.");
					conectado = true;
					MainCliente::serverDesconectado = false;
					MainCliente::cerrarConexion = false;

					offset += Protocolo::decodificar(bufferEntrada + offset,&mensaXml);
					char* idUsuario = mensaXml.getValor();

					Posicion posicion;

					// Se decodifica la posicion inicial desde donde arranca el avión
					offset += Protocolo::decodificar(bufferEntrada + offset, &posicion);

					Posicion posicionMapa;
					// Se decodifica la posicion del mapa, que tiene solo una componente Y
					offset += Protocolo::decodificar(bufferEntrada + offset, &posicionMapa);

					//se procede a decodificar el resto del mensaje
					//se decodifica el escenario completo
					offset += Protocolo::decodificar(bufferEntrada + offset,this->servidorXml);

					// Creo un hilo para escuchar los mensajes
					receptor=SDL_CreateThread(recibirMensajes, "recibirMensajes", &sock);

					Juego * insJuego = Juego::getInstance();
					insJuego->getJugador()->setIdCliente(atoi(idUsuario));
					insJuego->getJugador()->setPosicionAvion(posicion);

					Juego::getInstance()->readServidorXml(this->servidorXml);
					Juego::getInstance()->agregarObservador(this);
					Juego::getInstance()->ejecutar(this->servidorXml, posicionMapa.getPosY());

					// esto para desconectar al cliente al presionar la x del SDL_window
					SDL_Delay(1000);
					this->salir();
					this->opt=OPT_SALIR;
				}
				else if (strcmp(respuesta,FAKE_MENSAJE_02) == 0){
					// El server envia un mensaje al superar la cantidad de clientes

					Log::getInstance()->error(bufferEntrada);
					printf("Respuesta servidor:> %s\n",FAKE_MENSAJE_02);

					shutdown(sock,2);
					closesocket(sock);
				}
				else if (strcmp(respuesta, FAKE_MENSAJE_03) == 0) {
					// El server ya tiene un usuario igual y está conectado

					Log::getInstance()->error(bufferEntrada);
					printf("Respuesta servidor:> %s\n",FAKE_MENSAJE_03);

					desconectar();
				}
			}
		}
	}
	return 0;
}

int MainCliente::desconectar(){
	shutdown(sock,2);
	closesocket(sock);
	conectado=false;
	MainCliente::cerrarConexion = false;

	// WSACleanup();
	return 0;
}

int MainCliente::salir(){
	mapMensajes.clear(); // chequear si se liberan los string
	// liberar la memoria de los mensajes
	desconectar();
	return 0;
}

int MainCliente::enviar(){
	if(!conectado){
		Log::getInstance()->info(" Debe conectarse para enviar/recibir mensajes.");
		printf("Debe conectarse para enviar/recibir mensajes. \n");
		system("PAUSE");
		return -1;
	}

	char bufferEntrada[MAX_BUFFER];
	int id=-1,enc=0, len2 =2;
	int encRecibido = 0;
	printf("Para salir escriba 0 \n");

	// se deberian de cargar los mensajes desde el XML
	//TODO se cambia esto y se realiza en forma temprana, es decir a penas parsea
	//pues esto se realiza luego de parsear que carga la lista de mensajes del cliente
	//cargarIDMensajes();
	while(enc!=1){
		printf("Ingrese el ID del mensaje: ");
		string numstring;
		cin>>numstring;
		id=atoi(numstring.c_str());
		if(id==0)
			return 0;
		std::map<int,MensajeXml*>::iterator it;
		it=mapMensajes.find(id);
		if(it==mapMensajes.end()){
			printf("Mensaje no encontrado\n");
			enc=0;
		}else{
			//----------------
			//se envia de a uno los mensajes, por eso no hace falta un dato para la cantidad
			//total de mensajes (ahora trivial canMjs=1)
			MensajeXml* pMsj = it->second;
			char * buffEnvio = new char[MAX_BUFFER];
			int sizeBytesTotalLista = Protocolo::codificar(*pMsj,buffEnvio);
			//----------------
			if(chequearConexion(MensajeSeguro::enviar(sock,buffEnvio,sizeBytesTotalLista))<0) //enviar el texto que se ha introducido
				return -1;
			Log::getInstance()->debug(it->second->getValor());
			std::cout<< "Enviando:> ID:" << it->first << " => " << it->second->getValor();
			enc=1;
			// usar el socket y enviar el mensaje
			//recibir un mensaje
			//TODO 
			if(chequearConexion(len2 = MensajeSeguro::recibir(sock,bufferEntrada)) < 0)
				return -1;
			MensajeXml mensajeIN;
			Protocolo::decodificar(bufferEntrada,&mensajeIN);

			//bufferEntrada[len2] =0;
			Log::getInstance()->debug(mensajeIN.getValor());
			printf(" || respuesta servidor:> %s\n",mensajeIN.getValor());
			delete pMsj;
			delete buffEnvio;
		}

	}
	system("PAUSE");
	return 0;
}

/**
* muestra el menu y direcciona a las opciones
*
*/
int MainCliente::menu(){
	opt = 0;
	while (opt != OPT_SALIR){
		// TODO: Por el momento no borro la pantalla asi veo que va llegando 
		// system("CLS");	
		printf("\n%s\n", "------------------------------------------------------------------------");
		if(conectado)
			std::cout<<"Se encuentra: CONECTADO" <<std::endl;
		else
			std::cout<<"Se encuentra: DESCONECTADO" <<std::endl;
		printf("\n<1> CONECTAR");
		// printf("\n<2> DESCONECTAR");
		printf("\n<3> SALIR");
		// printf("\n<4> ENVIAR");
		printf("\n");
		string numstring;
		cin>>numstring;
		// scanf("%d",&id);
		//if(!esUnNumero(numstring)){
		//	cout<<"recuerde los valores tienen que ser numericos"<<endl;
		//	system("PAUSE");
		//}else{
		opt=atoi(numstring.c_str());
		//scanf("%d",&opt);
		switch (opt){
		case OPT_CONECTAR:
			conectar();
			break;
	/*	case OPT_DESCONECTAR:
			desconectar();
			break; */
		case OPT_SALIR:
			salir();
			break;
	/*	case OPT_ENVIAR:
			enviar();
			break; */
		}
	}
	return 0;
}

void MainCliente::actualizar(void* argv[]){

	EstadoAvion* mov = (EstadoAvion*)argv[0];

	EstadoAvionXml* msjMov = new EstadoAvionXml(mov->getId(), mov->getFrame(), mov->getPosX(), mov->getPosY());
	
	std::list<EstadoProyectil*>::iterator it;
	std::list<EstadoProyectil*> listaP = mov->getEstadosProyectiles();

	for (it = listaP.begin(); it != listaP.end(); it++) {
		msjMov->agregarEstadoProyectil(new EstadoProyectilXml((*it)->getFrame(),(*it)->getPosX(), (*it)->getPosY()));
	}

	char * buffEnvio = new char[MAX_BUFFER];
	int sizeBytesTotalLista = Protocolo::codificar(*msjMov,buffEnvio);
	// TODO: test

	if(chequearConexion(MensajeSeguro::enviar(sock,buffEnvio,sizeBytesTotalLista))<0) { //enviar el texto que se ha introducido
		printf("No se pudo enviar el movimiento");
		// TODO: En este caso si el server esta desconectado deberiamos frenar el jeguo.
	}

	//Recuerdo que este metodo es solo para cuando los proyectiels esten en 
	//memoria dinamica
	msjMov->liberarMemoriaProyectiles();
	delete[] buffEnvio;
	delete msjMov;
	delete mov;
}
