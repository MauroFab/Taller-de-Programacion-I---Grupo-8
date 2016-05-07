#ifndef _SERVIDORXML_H_
#define _SERVIDORXML_H_
/* @autor sabris
 */

#include "EscenarioXml.h"
#include "VentanaXml.h"
#include "SpriteXml.h"
#include "AvionXml.h"
#include "../IGenericaVO.h"

#define MAX_SPRITES	300
#define MAX_AVIONES	10

class ServidorXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int cantidadMaximaClientes;
	int puerto;
	VentanaXml ventanaXml;
	EscenarioXml escenarioXml;
	//BUG-001 cambiar la lista de elementos
	SpriteXml * listaSprite[MAX_SPRITES];
	int canSprs;
	AvionXml * listaAviones[MAX_AVIONES];
	int canAvs;	
public:
	ServidorXml();
	virtual ~ServidorXml();
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setCantidadMaximaClientes(int cantidadMaximaClientes);
	int getCantidadMaximaClientes();
	void setPuerto(int puerto);
	int getPuerto();
	void setVentanaXml(const VentanaXml &ventanaXml);
	VentanaXml * getVentanaXmlCopy();
	void setEscenarioXml(const EscenarioXml &escenarioXml);
	/*const */EscenarioXml * getEscenarioXmlCopy();
	void addSprite(SpriteXml * sprite,int pos);
	//listado de punteros
	SpriteXml * * getListaSprites();
	int getCanSprs();	
	void addAvion(AvionXml * avion,int pos);
	//listado de punteros a Aviones
	AvionXml * * getListaAviones();
	int getCanAvs();
	void toString(TCadena1000 cadena);

};

#endif //_SERVIDORXML_H_
