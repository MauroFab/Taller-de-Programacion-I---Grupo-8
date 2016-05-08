#include "../../juego/Juego.h"
#include "MainCliente.h"

MainCliente::MainCliente(){
	this->dirXML.assign("");
	this->conex = 0;
	this->len = 0;
	this->conectado = false;
	// aca deberia de obtener el ip, port y cargar los mensajes en el map
	this->ip = "";
	this->port = -1;
	// si usan el principal comentar inicializar()
	this->parserx = new ParserXml();
	this->servidorXml = new ServidorXml();
}

MainCliente::~MainCliente(){
	delete this->parserx;
	if (this->servidorXml != NULL)
		delete this->servidorXml;
}

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
	std::cout<< port<<std::endl;

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

	//resolvemos el nombre de dominio localhost, esto se resolver� a 127.0.0.1
	host=gethostbyname(ip.c_str());

	//creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock==-1)
	{
		Log::getInstance()->error(" al crear el socket.");
		printf("Error al crear el socket");
		return -1;
	}
	setsockopt (sock, IPPROTO_TCP, SO_REUSEADDR | SOCK_STREAM, (char*)&c, sizeof(int));
	//Definimos la direcci�n a conectar que hemos recibido desde el gethostbyname
	//y decimos que el puerto al que deber� conectar es el 9999 con el protocolo ipv4
	direc.sin_family=AF_INET;
	direc.sin_port=htons(atoi(port.c_str()));
	direc.sin_addr = *((struct in_addr *)host->h_addr);
	memset(direc.sin_zero,0,8);

	return 0;
}

int MainCliente::conectar(){
	inicializarConexion();
	if(conectado==true){
		Log::getInstance()->warn(" el cliente ya se encuentra conectado.");
		printf("ya se encuentra conectado \n"); //WARN?
	}
	else{
		//Intentamos establecer la conexi�n
		conex=connect(sock,(sockaddr *)&direc, sizeof(sockaddr));
		if (conex==-1) //si no se ha podido conectar porque no se ha encontrado el host o no est� el puerto abierto
		{
			Log::getInstance()->error(" no se ha podido conectar.");
			printf("No se ha podido conectar\n");
			printf("%i", conex);
			return -1;
		}
		else{

			int len2 = 2;
			char bufferEntrada[MAX_BUFFER];

			len2 = recv(sock,bufferEntrada,MAX_BUFFER,0);

			if (len2 <= 0){
				// Es un error
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

					//se procede a decodificar el resto del mensaje
					//se decodifica el escenario completo
					offset += Protocolo::decodificar(bufferEntrada + offset,this->servidorXml);
					TCadena1000 cadena;
					this->servidorXml->toString(cadena);
					printf("%s",cadena);

					//Juego::getInstance()->cargarConfiguracion(this->servidorXml);
					Juego::getInstance()->ejecutar();

				}
				else if (strcmp(respuesta,FAKE_MENSAJE_02) == 0){
					// El server envia un mensaje al superar la cantidad de clientes
	
					Log::getInstance()->error(bufferEntrada);
					printf("Respuesta servidor:> %s\n",bufferEntrada);
	
					shutdown(sock,2);
					closesocket(sock);
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

	if(conectado==false){ //!conectado
		Log::getInstance()->info(" debe conectarse para enviar/recibir mensajes.");
		printf("debe conectarse para enviar/recibir mensajes. \n");
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
		// scanf("%d",&id);
		//if(!esUnNumero(numstring)){
		//	cout<<"recuerde los valores tienen que ser numericos"<<endl;
		//	system("PAUSE");
		//	return -1;
		//}
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
			if(chequearConexion(send(sock,buffEnvio,sizeBytesTotalLista,0))<0) //enviar el texto que se ha introducido
				return -1;
			Log::getInstance()->debug(it->second->getValor());
			std::cout<< "Enviando:> ID:" << it->first << " => " << it->second->getValor();
			enc=1;
			// usar el socket y enviar el mensaje
			//recibir un mensaje
			//TODO 
			if(chequearConexion(len2 = recv(sock,bufferEntrada,MAX_BUFFER,0)) < 0)
				return -1;
			MensajeXml mensajeIN;
			Protocolo::decodificar(bufferEntrada,&mensajeIN);
			
			//bufferEntrada[len2] =0;
			Log::getInstance()->debug(mensajeIN.getValor());
			printf(" || respuesta servidor:> %s\n",mensajeIN.getValor());
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
	int opt = 0;
	while (opt != OPT_SALIR){
		// TODO: Por el momento no borro la pantalla asi veo que va llegando 
		// system("CLS");	
		printf("\n%s\n", "------------------------------------------------------------------------");
		if(conectado)
			std::cout<<"Se encuentra: CONECTADO" <<std::endl;
		else
			std::cout<<"Se encuentra: DESCONECTADO" <<std::endl;
		printf("\n<1> CONECTAR");
		printf("\n<2> DESCONECTAR");
		printf("\n<3> SALIR");
		printf("\n<4> ENVIAR");
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
			case OPT_DESCONECTAR:
				desconectar();
				break;
			case OPT_SALIR:
				salir();
				break;
			case OPT_ENVIAR:
				enviar();
				break;
		}
		//}
	}
	return 0;
}