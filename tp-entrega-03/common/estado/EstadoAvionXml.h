#ifndef _ESTADOAVIONXML_H_
#define _ESTADOAVIONXML_H_

#include <string.h>
#include <list>

using namespace std;

#include "EstadoProyectilXml.h"
#include "../IGenericaVO.h"

class EstadoAvionXml : public IGenericaVO
{
protected:
	int sizeBytes;
	int id;
	int frame;
	int posX;
	int posY;
	list<EstadoProyectilXml*> estadosProyectiles;

public:
	
	EstadoAvionXml();
	EstadoAvionXml(int id,int frame, int posX, int posY);
	virtual ~EstadoAvionXml();
    
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

	list<EstadoProyectilXml*> getEstadosProyectiles();
	void agregarEstadoProyectil(EstadoProyectilXml* estadoProyectil);	

	void toString(TCadena1000 cadena);	

	//Cuidado con este metodo. A veces los proyectiles que se le mandaron fueron en forma
	//estatica. Y otras veces en forma dinamica. En los casos donde esta con memoria estatica
	//No llamar
	void EstadoAvionXml::liberarMemoriaProyectiles();
};

#endif //_ESTADOAVIONXML_H_
