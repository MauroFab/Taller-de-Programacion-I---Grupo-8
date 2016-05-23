#ifndef _ESTADOAVIONXML_H_
#define _ESTADOAVIONXML_H_

#include <string.h>
#include <list>

using namespace std;

#include "EstadoProyectilXml.h"
#include "../Mensaje.h"

class EstadoAvionXml : public Mensaje
{
protected:
	int frame;
	int posX;
	int posY;
	list<EstadoProyectilXml*> estadosProyectiles;

public:
	
	EstadoAvionXml();
	EstadoAvionXml(int id,int tipo, int posX, int posY);
	virtual ~EstadoAvionXml();
    
	// Retorna el tipo de mensaje
	int getTipo();

	int getSizeBytes();
	void calculateSizeBytes();

	void setId(int id);
	int getId();
	
	void setFrame(int frame);
	int getFrame();
	
	void setPosX(int posX);
	int getPosX();

	void setPosY(int posY);
	int getPosY();

	void agregarEstadoProyectil(EstadoProyectilXml* estadoProyectil);
	list<EstadoProyectilXml*> getEstadosProyectiles();

	void eliminarProyectiles();

	void toString(TCadena1000 cadena);	

	//Cuidado con este metodo. A veces los proyectiles que se le mandaron fueron en forma
	//estatica. Y otras veces en forma dinamica. En los casos donde esta con memoria estatica
	//No llamar
	void EstadoAvionXml::liberarMemoriaProyectiles();


};

#endif //_ESTADOAVIONXML_H_
