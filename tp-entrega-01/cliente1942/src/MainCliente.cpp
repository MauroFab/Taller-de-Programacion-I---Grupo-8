#include "MainCliente.h"

MainCliente::MainCliente()
{
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
		return -1;
	}

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
		printf("No se ha podido conectar\n");
		printf("%i", conex);
		return -1;
	}
	
	printf("[escribe el texto a enviar o 'salir' para salir ]\n");
	while (len!=-1 && (strcmp(Buffer,"salir")!=0)){ //mientras el socket no se haya desconectado
		//y no se escriba salir
		printf("Texto a enviar:");
		scanf("%s",Buffer); //pedir texto a enviar por pantalla
		len=send(sock,Buffer,strlen(Buffer),0); //enviar el texto que se ha introducido
	}
	if(strcmp(Buffer,"salir") != 0){ //si no se escribio salir
		printf("El mensaje no se pudo enviar porque el servidor termino la conexion\n");
		printf("Introduzca cualquier tecla para salir\n");
		scanf("%s",Buffer);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}
int MainCliente::optConectar(){
	printf("\n OPT_CONECTAR\n ");
/*	
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
		return -1;
	}

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
		printf("No se ha podido conectar\n");
		printf("%i", conex);
		return -1;
	}	
*/	
	return 0;
}
int MainCliente::optDesconectar(){
	printf("\n OPT_DESCONECTAR\n ");
/*	
	closesocket(sock);
	WSACleanup();
*/	
	return 0;
}
int MainCliente::optSalir(){
	printf("\n OPT_SALIR\n ");
	return 0;
}
int MainCliente::optEnviar(){
	printf("\n OPT_ENVIAR\n ");
	return 0;
}
int MainCliente::optCiclar(){
	printf("\n OPT_CICLAR");
	return 0;
}
/**
 * muestra el menu y direcciona a las opciones
 * 
 */
int MainCliente::menu(){
	int opt = 0;
	while (opt != OPT_SALIR){
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