#include "MainCliente.h"
#include "../../common/Log.h"

MainCliente::MainCliente(string dirXml):dirXML(dirXml),conex(0),len(0),conectado(false)
{

	// aca deberia de obtener el ip, port y cargar los mensajes en el map
	ip="localhost";
	port="9999";
	// si usan el principal comentar inicializar()

}

MainCliente::~MainCliente()
{
}

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
	printf("\n OPT_CONECTAR\n ");
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
		conectado=true;
	}
	return 0;
}
int MainCliente::optDesconectar(){
	printf("\n OPT_DESCONECTAR\n ");
	shutdown(sock,2);
	closesocket(sock);
	conectado=false;
	// WSACleanup();
	return 0;
}
int MainCliente::optSalir(){
	printf("\n OPT_SALIR\n ");
	mapMensajes.clear(); // chequear si se liberan los string
	// liberar la memoria de los mensajes
	optDesconectar();
	return 0;
}
// auxiliar de carga de mensajes que deberia hacerse desde el xml
int MainCliente::cargarIDMensajes(){

	//Esto desapareceria
	for(int i=0;i<20;i++){
		std::stringstream ss;
		ss << "mensaje";
		ss << i+1;

		mapMensajes.insert ( std::pair<int,string>(i+1,ss.str()));
	}
	//hasta aca
	std::map<int,string>::iterator it = mapMensajes.begin();
	for (it=mapMensajes.begin(); it!=mapMensajes.end(); ++it)
		std::cout<< "ID:" << it->first << " => " << it->second << std::endl;
	return 0;
}
int MainCliente::optEnviar(){
	if(conectado==false){ //!conectado

		Log::getInstance()->info(" debe conectarse para enviar/recibir mensajes.");
		printf("Tiene que estar conectado para que puedas enviar/recibir \n");

		return -1;
	}
	char bufferEntrada[1024];
	int id=-1,enc=0, len2 =2;
	int encRecibido = 0;
	printf("Para salir escriba 0 \n");
	// se deberian de cargar los mensajes desde el XML 
	cargarIDMensajes();
	while(enc!=1){
		printf("Ingrese el ID del mensaje: ");
		scanf("%d",&id);
		if(id==0)
			return 0;
		std::map<int,string>::iterator it;
		it=mapMensajes.find(id);
		if(it==mapMensajes.end()){
			printf("Mensaje no encontrado\n");
			enc=0;
		}else{

			len=send(sock,it->second.c_str(),strlen(it->second.c_str()),0); //enviar el texto que se ha introducido
			
			Log::getInstance()->debug(it->second.c_str());
			printf("Enviando el mensaje: %s Falta terminar\n",it->second.c_str());
			enc=1;
			
			// usar el socket y enviar el mensaje
			//recibir un mensaje
			len2 = recv(sock,bufferEntrada,1023,0);
			bufferEntrada[len2] =0;

			Log::getInstance()->debug(bufferEntrada);
			printf("Recibida respuesta: %s\n",bufferEntrada);
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
		printf("Tiene que estar conectado para que puedas enviar/recibir \n");
		return -1;
	}
	int tiempo=0;
	char bufferEntrada[1024];
	int len2 = -1;
	char mensaje[]="FALTA HACER LA LISTA CIRCULAR Y ENVIAR";
	ciclar_t ciclos;
	ciclos.terminarCiclar=false;
	printf("por cuanto tiempo desea ciclar(ms):");
	scanf("%d",&(ciclos.tiempo));
	SDL_Thread* hiloCiclar=SDL_CreateThread(MainCliente::contarCiclo, "contarCiclo", (void*)&ciclos);
	while(ciclos.terminarCiclar==false){
		printf("FALTA HACER la lista circular y enviar ......\n");
		len=send(sock,mensaje,strlen(mensaje),0);
		len2 = recv(sock,bufferEntrada,1023,0);
		bufferEntrada[len2] =0;
		printf("Recibida respuesta: %s\n",bufferEntrada);
	}

	SDL_WaitThread(hiloCiclar, NULL);
	printf("\n OPT_CICLAR");
	return 0;
}

int MainCliente::optErronea(){
	printf("\n No existe la opcion marcada, vuelva a escribirla");
	return 0;
}

/**
* muestra el menu y direcciona a las opciones
* 
*/
int MainCliente::menu(){
	int opt = 0;
	while (opt != OPT_SALIR){
		// system("CLS");
		printf("\n<1> CONECTAR");
		printf("\n<2> DESCONECTAR");
		printf("\n<3> SALIR");
		printf("\n<4> ENVIAR");
		printf("\n<5> CICLAR");
		printf("\n");					
		scanf("%d",&opt);
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
			break;
		}
	}
	return 0;
}