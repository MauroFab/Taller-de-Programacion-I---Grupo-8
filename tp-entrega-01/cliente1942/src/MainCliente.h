#ifndef _MAINCLIENTE_H_
#define _MAINCLIENTE_H_

#include <winsock2.h> //la cabezera para usar las funciones de winsock
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#define OPT_CONECTAR	1
#define OPT_DESCONECTAR 2
#define OPT_SALIR		3
#define OPT_ENVIAR		4
#define OPT_CICLAR		5

class MainCliente
{
private:
	SOCKET sock;	
public:
	MainCliente();
	virtual ~MainCliente();
	int principal();
	int menu();
	
	int optConectar();
	int optDesconectar();
	int optSalir();
	int optEnviar();
	int optCiclar();
	
};

#endif //_MAINCLIENTE_H_
