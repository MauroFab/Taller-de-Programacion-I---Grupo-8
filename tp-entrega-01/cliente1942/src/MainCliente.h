#ifndef _MAINCLIENTE_H_
#define _MAINCLIENTE_H_

#include <winsock2.h> //la cabezera para usar las funciones de winsock
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib> 
#pragma comment(lib,"ws2_32.lib")

#define OPT_CONECTAR	1
#define OPT_DESCONECTAR 2
#define OPT_SALIR		3
#define OPT_ENVIAR		4
#define OPT_CICLAR		5

using std::string;
using std::map;
using std::pair;

class MainCliente
{
private:
	SOCKET sock;	
	map<int,string> mapMensajes;
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
	int optErronea();
	int cargarIDMensajes();
	
};

#endif //_MAINCLIENTE_H_
