#include <stdio.h>
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>

#pragma comment(lib,"ws2_32.lib")
using std::string;
using std::cout;
using std::cin;
using std::clog;
using std::cerr;
using std::ofstream;
class Common_Socket
{
public:
	Common_Socket(SOCKET& socket);
	Common_Socket(string ip,string port);
	Common_Socket(string port);
	int enviar(const string& datos);
	int recibir(string& datos);	
int cerrar();
	virtual ~Common_Socket(void);
protected:
	
	    WSADATA wsa;
		SOCKET sock;
struct sockaddr_in local;
int len;
	char Buffer[1024];
};

