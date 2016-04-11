#ifndef _SERVIDORXML_H_
#define _SERVIDORXML_H_

class ServidorXml
{
private:
	int cantidadMaximaClientes;
	int puerto;
public:
	ServidorXml();
	virtual ~ServidorXml();
	void setCantidadMaximaClientes(int cantidadMaximaClientes);
	int getCantidadMaximaClientes();
	void setPuerto(int puerto);
	int getPuerto();
};

#endif //_SERVIDORXML_H_
