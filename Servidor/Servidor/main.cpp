#include <iostream>
#include <string>
#include "Servidor_Socket.h"
using std::string;
int main()

{
	int len=-1;
	string datos;
	string ip="localhost";
	string puerto="9999";
	Servidor_Socket Ssocket(ip,puerto);
	Ssocket.escuchar();
	while (len!=0) //mientras estemos conectados con el otro pc
	{
		len=Ssocket.recibir(datos);
		if (strcmp(datos.c_str(),"salir")==0)
			len=0;
	}
	return 0;
}
