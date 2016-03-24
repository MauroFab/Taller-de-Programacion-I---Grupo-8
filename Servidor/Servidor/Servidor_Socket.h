#include "../../Common/Common_Socket.h"
class Servidor_Socket :
	public Common_Socket
{
public:
	Servidor_Socket(SOCKET& socket);
	Servidor_Socket(string ip,string port);
	Servidor_Socket(string port);
	int escuchar();
	~Servidor_Socket(void);
};

