#ifndef _CONEXIONXML_H_
#define _CONEXIONXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define LARGO_IP	16

class ConexionXml
{
private:
	//255.255.255.255
	// 4 + 4 + 4 + 3 +'\0'
	char ip[LARGO_IP];
	int puerto;
public:
	ConexionXml();
	ConexionXml(char * ip, int puerto){
		strcpy(this->ip,ip);
		this->puerto = puerto;
	};
	//constructor copia
	ConexionXml(const ConexionXml & conexionXml){
		strcpy(this->ip,conexionXml.ip);
		this->puerto = conexionXml.puerto;
	}
	virtual ~ConexionXml();
	void setIp(char* ip);
	char* getIp();
	void setPuerto(int puerto);
	int getPuerto();
	ConexionXml & operator = (const ConexionXml & source);
};

#endif //_CONEXIONXML_H_
