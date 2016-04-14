#include "Common_Socket.h"

Common_Socket::Common_Socket(SOCKET& socket){
	memcpy(&sock,&socket,sizeof(socket));
}

Common_Socket::Common_Socket(string ip,string port){
	//Inicializamos
WSAStartup(MAKEWORD(2,0),&wsa);

	//Creamos el socket
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	//defnimos dirección por defecto, ipv4 y el puerto 9999
	local.sin_family = AF_INET;
local.sin_addr.s_addr = INADDR_ANY;
local.sin_port = htons(9999);
}

Common_Socket::Common_Socket(string port){
	Common_Socket("localhost",port);
}

int Common_Socket::enviar(const string& datos){return 0;}

int Common_Socket::recibir(string& datos){

	int len=recv(sock,Buffer,1023,0); //recibimos los datos que envie
		if (len>0) //si seguimos conectados
		{
			Buffer[len]=0; //le ponemos el final de cadena
			printf("Texto recibido:%s\n",Buffer); //imprimimos la cadena recibida
		}
	// solo irve para texto cambiar por streambuff para datos
		datos=string(Buffer);


	return len;
}

int Common_Socket::cerrar(){
	
	closesocket(sock);
	WSACleanup();
	return 0;
}

Common_Socket::~Common_Socket(void)
{
}
