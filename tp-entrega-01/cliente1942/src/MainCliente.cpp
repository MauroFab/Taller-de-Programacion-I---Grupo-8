#include "MainCliente.h"


MainCliente::MainCliente(){
	dirXML.assign("");
	conex = 0;
	len = 0;
	conectado = false;
	// aca deberia de obtener el ip, port y cargar los mensajes en el map
	ip = "";
	port = -1;
	// si usan el principal comentar inicializar()
	parserx = new ParserXml();

}

MainCliente::~MainCliente(){
	delete this->parserx;
}

void MainCliente::parsearArchivoXml(int argc, char* argv[]){
	getParserXml()->cargarXmlCliente(argc,argv);
	int res = getParserXml()->validarXmlArchivoCliente();
	if (res < 0){
		printf("\nERROR: Error semantico\n");
	}
	else{
		//luego de la carga crea los datos a partir del XML
		ClienteXml * clienteXml = getParserXml()->createDataClienteXml();
		printf("\nOK\n");
		//se cargan los datos desde el cliente
		//copia la ip
		this->ip.assign(clienteXml->getConexionXmlCopy()->getIp());
		//copia el puerto
		int puerto = clienteXml->getConexionXmlCopy()->getPuerto();
		char cadena[10];
		sprintf(cadena,"%d",puerto);
		this->port.assign(cadena);
		std::cout<< port<<std::endl;
		//carga un listado, 
		//que luego viajara al cliente
		//aca ya se puede cargar el mapa
		cargarIDMensajes(clienteXml);

		// luego de usarlo se debe borrar
		delete clienteXml;
	}

}

ParserXml * MainCliente::getParserXml(){
	return this->parserx;
}
/*
int MainCliente::principal(){
WSADATA wsa;
//	SOCKET sock;
struct hostent *host;
struct sockaddr_in direc;
int conex=0;
char Buffer[1024]="";
int len=0;
//Inicializamos
WSAStartup(MAKEWORD(2,2),&wsa);

//resolvemos el nombre de dominio localhost, esto se resolverá a 127.0.0.1
host=gethostbyname("localhost");

//creamos el socket
sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if (sock==-1)
{
printf("Error al crear el socket");
Log::getInstance()->error(" al crear el socket.");

return -1;
}
setsockopt (sock, IPPROTO_TCP, SO_REUSEADDR | SOCK_STREAM, (char*)&c, sizeof(int));
//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
//y decimos que el puerto al que deberá conectar es el 9999 con el protocolo ipv4
direc.sin_family=AF_INET;
direc.sin_port=htons(9999);
direc.sin_addr = *((struct in_addr *)host->h_addr);
memset(direc.sin_zero,0,8);

//Intentamos establecer la conexión
conex=connect(sock,(sockaddr *)&direc, sizeof(sockaddr));
if (conex==-1) //si no se ha podido conectar porque no se ha encontrado el host o no
//está el puerto abierto
{
Log::getInstance()->info("No se ha podido conectar al server.");
printf("No se ha podido conectar\n");
printf("%i", conex);

return -1;
}

printf("[escribe el texto a enviar o 'salir' para salir ]\n");
printf("Texto a enviar:");
scanf("%s",Buffer); //pedir texto a enviar por pantalla
while (len!=-1 && (strcmp(Buffer,"salir")!=0)){ //mientras el socket no se haya desconectado
//y no se escriba salir
len=send(sock,Buffer,strlen(Buffer),0); //enviar el texto que se ha introducido
printf("Texto a enviar:");
scanf("%s",Buffer); //pedir texto a enviar por pantalla
}

if(strcmp(Buffer,"salir") != 0){ //si no se escribio salir

Log::getInstance()->error("El mensaje no se pudo enviar porque el servidor termino la conexion.");
printf("El mensaje no se pudo enviar porque el servidor termino la conexion\n");
printf("Introduzca cualquier tecla para salir\n");
scanf("%s",Buffer);
}
closesocket(sock);
WSACleanup();
return 0;
}
*/

bool MainCliente::esUnNumero(string s){
	for(int i=0;i<s.length();i++)
		if(!isdigit(s[i]))
			return false;
	return true;
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

int MainCliente::inicializar(){

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
	setsockopt (sock, IPPROTO_TCP, SO_REUSEADDR | SOCK_STREAM, (char*)&c, sizeof(int));
	//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
	//y decimos que el puerto al que deberá conectar es el 9999 con el protocolo ipv4
	direc.sin_family=AF_INET;
	direc.sin_port=htons(atoi(port.c_str()));
	direc.sin_addr = *((struct in_addr *)host->h_addr);
	memset(direc.sin_zero,0,8);

	return 0;
}
int MainCliente::optConectar(){
	inicializar();
	if(conectado==true){
		Log::getInstance()->warn(" el cliente ya se encuentra conectado.");
		printf("ya se encuentra conectado \n"); //WARN?
	}
	else{
		//Intentamos establecer la conexión
		conex=connect(sock,(sockaddr *)&direc, sizeof(sockaddr));
		if (conex==-1) //si no se ha podido conectar porque no se ha encontrado el host o no está el puerto abierto
		{
			Log::getInstance()->error(" no se ha podido conectar.");
			printf("No se ha podido conectar\n");
			printf("%i", conex);
			return -1;
		}
		else{

			int len2 =2;
			char bufferEntrada[1024];

			len2=recv(sock,bufferEntrada,1023,0);

			if(len2 == 18){
				// Si el server no envia respuesta es que la conexion ha sido satisfactoria
				Log::getInstance()->info("El cliente se ha conectado correctamente.");
				conectado = true;
			}
			else if (len2 > 0){
				// El server envia un mensaje al superar la cantidad de clientes
				bufferEntrada[len2] =0;

				Log::getInstance()->error(bufferEntrada);
				printf("Respuesta servidor:> %s\n",bufferEntrada);

				shutdown(sock,2);
				closesocket(sock);
			}
			else{
				// Es un error
				chequearConexion(len2);
			}
		}
	}
	return 0;
}
int MainCliente::optDesconectar(){
	shutdown(sock,2);
	closesocket(sock);
	conectado=false;
	// WSACleanup();
	return 0;
}
int MainCliente::optSalir(){
	mapMensajes.clear(); // chequear si se liberan los string
	// liberar la memoria de los mensajes
	optDesconectar();

	return 0;
}
// auxiliar de carga de mensajes que deberia hacerse desde el xml
int MainCliente::cargarIDMensajes(ClienteXml * clienteXml){
	int idx = 0;
	MensajeXml ** listaMsjs = clienteXml->getListaMensajes();
	int totMsjs = clienteXml->getCanMsjs();
	while (idx < totMsjs){
		MensajeXml * pMensj = listaMsjs[idx];
		string valStr(pMensj->getValor());
		mapMensajes.insert ( std::pair<int,string>(pMensj->getId(),valStr.c_str()));
		idx++;
	}
	//Esto desapareceria ==>desaparecio
	/*
	for(int i=0;i<20;i++){
	std::stringstream ss;
	ss << "mensaje";
	ss << i+1;

	mapMensajes.insert ( std::pair<int,string>(i+1,ss.str()));
	}
	*/
	//hasta aca
	return 0;
}
int MainCliente::optEnviar(){

	if(conectado==false){ //!conectado

		Log::getInstance()->info(" debe conectarse para enviar/recibir mensajes.");
		printf("debe conectarse para enviar/recibir mensajes. \n");
		system("PAUSE");
		return -1;
	}
	
	char bufferEntrada[1024];
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
		if(!esUnNumero(numstring)){
			cout<<"recuerde los valores tienen que ser numericos"<<endl;
			system("PAUSE");
			return -1;
		}
		id=atoi(numstring.c_str());
		if(id==0)
			return 0;
		std::map<int,string>::iterator it;
		it=mapMensajes.find(id);
		if(it==mapMensajes.end()){
			printf("Mensaje no encontrado\n");
			enc=0;
		}else{

			if(chequearConexion(send(sock,it->second.c_str(),strlen(it->second.c_str()),0))<0) //enviar el texto que se ha introducido
				return -1;
			Log::getInstance()->debug(it->second.c_str());
			std::cout<< "Enviando:> ID:" << it->first << " => " << it->second;
			enc=1;
			// usar el socket y enviar el mensaje
			//recibir un mensaje
			if(chequearConexion(len2=recv(sock,bufferEntrada,1023,0))<0)
				return -1;
			bufferEntrada[len2] =0;

			Log::getInstance()->debug(bufferEntrada);
			printf(" || respuesta servidor:> %s\n",bufferEntrada);
		}

	}
	system("PAUSE");
	return 0;
}
int MainCliente::contarCiclo(void* sciclo){
	ciclar_t* ciclos=(ciclar_t*)sciclo;
	SDL_Delay(ciclos->tiempo);
	ciclos->terminarCiclar=true;
	return 0;
}
int MainCliente::optCiclar(){
	if(conectado==false){ //!conectado

		Log::getInstance()->info(" debe conectarse para enviar/recibir mensajes.");
		printf(" debe conectarse para enviar/recibir mensajes.\n");
		system("PAUSE");
		return -1;
	}
	int tiempo=0;
	char bufferEntrada[1024];
	int len2 = -1;
	ciclar_t ciclos;
	ciclos.terminarCiclar=false;
	printf("por cuanto tiempo desea ciclar(ms):");
	string numstring;
	cin>>numstring;
	// scanf("%d",&id);
	if(!esUnNumero(numstring)){
		cout<<"recuerde los valores tienen que ser numericos"<<endl;
		system("PAUSE");
		return -1;
	}
	ciclos.tiempo=atoi(numstring.c_str());

	//scanf("%d",&(ciclos.tiempo));
	SDL_Thread* hiloCiclar=SDL_CreateThread(MainCliente::contarCiclo, "contarCiclo", (void*)&ciclos);
	std::map<int,string>::iterator it = mapMensajes.begin();
	while(ciclos.terminarCiclar==false){

		if(it==mapMensajes.end())
			it=mapMensajes.begin();
		std::cout<< "Enviando:> ID:" << it->first << " => " << it->second;
		if(chequearConexion(send(sock,it->second.c_str(),strlen(it->second.c_str()),0))<0)
			return -1;
		if(chequearConexion(len2=recv(sock,bufferEntrada,1023,0))<0)
			return -1;
		bufferEntrada[len2] =0;
		printf(" || respuesta servidor:> %s\n",bufferEntrada);
		it++;
	}

	SDL_WaitThread(hiloCiclar, NULL);
	system("PAUSE");
	return 0;
}

int MainCliente::optErronea(){
	printf("\n No existe la opcion marcada\n");
	system("PAUSE");
	return 0;
}

/**
* muestra el menu y direcciona a las opciones
* 
*/

int MainCliente::cargarMenuMsj(){
	std::map<int,string>::iterator it = mapMensajes.begin();
	std::cout<<""<<std::endl;
	for (it=mapMensajes.begin(); it!=mapMensajes.end(); ++it)
		std::cout<< "\t ID:" << it->first << " => " << it->second << std::endl;
	return 0;
}
int MainCliente::menu(){
	int opt = 0;
	while (opt != OPT_SALIR){
		system("CLS");
		if(conectado)
			std::cout<<"\t se encuentra: CONECTADO" <<std::endl;
		else
			std::cout<<"\t se encuentra: DESCONECTADO" <<std::endl;
		printf("\n<1> CONECTAR");
		printf("\n<2> DESCONECTAR");
		printf("\n<3> SALIR");
		printf("\n<4> ENVIAR");
		cargarMenuMsj();
		printf("\n<5> CICLAR");
		printf("\n");
		string numstring;
		cin>>numstring;
		// scanf("%d",&id);
		if(!esUnNumero(numstring)){
			cout<<"recuerde los valores tienen que ser numericos"<<endl;
			system("PAUSE");
		}else{
			opt=atoi(numstring.c_str());
			//scanf("%d",&opt);
			switch (opt)
			{
			case OPT_CONECTAR:{
				optConectar();
							  }
							  break;
			case OPT_DESCONECTAR:{
				optDesconectar();
								 }
								 break;
			case OPT_SALIR:{
				optSalir();
						   }
						   break;
			case OPT_ENVIAR:{
				optEnviar();
							}
							break;
			case OPT_CICLAR:{
				optCiclar();
							}
							break;
			default:
				optErronea();
				break;
			}
		}
	}
	return 0;
}