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
#define MAX_AVIONES	40
#define MAX_ESCENARIOS 10

#define M_MODO_PRACTICA_COLABORACION	1
#define M_MODO_PRACTICA_EQUIPO			2
#define M_MODO_NORMAL_COLABORACION		3
#define M_MODO_NORMAL_EQUIPO			4

#define S_MODO_PRACTICA_COLABORACION	"practica_colaboracion"
#define S_MODO_PRACTICA_EQUIPO			"practica_equipo"
#define S_MODO_NORMAL_COLABORACION		"normal_colaboracion"
#define S_MODO_NORMAL_EQUIPO			"normal_equipo"

class ServidorXml : public IGenericaVO
{
private:
	int sizeBytes;
	int cantidadMaximaClientes;
	int puerto;
	int modo;
	VentanaXml ventanaXml;
	EscenarioXml * listaEscenario[MAX_ESCENARIOS];
	int canEsc;
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
	void setCantidadMaximaClientes(int cantidadMaximaClientes);
	int getCantidadMaximaClientes();
	void setPuerto(int puerto);
	int getPuerto();
	void setModo(int modo);
	int getModo();
	void setVentanaXml(const VentanaXml &ventanaXml);
	VentanaXml * getVentanaXmlCopy();

	void addEscenario(EscenarioXml * escenario,int pos);
	EscenarioXml * * getListaEscenario();
	int getCanEsc();

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
