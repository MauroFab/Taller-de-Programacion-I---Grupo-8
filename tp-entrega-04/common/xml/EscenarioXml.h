#ifndef _ESCENARIOXML_H_
#define _ESCENARIOXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "FondoXml.h"
#include "ElementoXml.h"
#include "AvionEnemigoXml.h"
#include "PowerUpXml.h"
#include "../IGenericaVO.h"

#define MAX_ELEMENTOS	300
#define MAX_ENEMIGOS 10
#define MAX_POWERUPS 10

class EscenarioXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int ancho;
	int alto;
	FondoXml fondoXml;
	//BUG-003 cambiar la lista de elementos
	ElementoXml * lista[MAX_ELEMENTOS];	
	int canElems;
	AvionEnemigoXml * listaEnemigos[MAX_ENEMIGOS];
	int canEnes;
	PowerUpXml * listaPowerUp[MAX_POWERUPS];
	int canPows;
public:
	EscenarioXml();
	EscenarioXml(int id);
	virtual ~EscenarioXml();
	//para la misma clase
    EscenarioXml & operator = (const EscenarioXml & source);	
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setAncho(int ancho);
	int getAncho();
	void setAlto(int alto);
	int getAlto();	
	void setFondoXml(const FondoXml &fondoXml);
	/*const */FondoXml * getFondoXmlCopy();
	void addElemento(ElementoXml * elemento,int pos);
	//listado de punteros
	ElementoXml * * getListaElementos();
	int getCanElems();

	void addEnemigo(AvionEnemigoXml * enemigo,int pos);
	//listado de punteros a Enemigos
	AvionEnemigoXml * * getListaEnemigos();
	int getCanEnes();

	void addPowerUp(PowerUpXml * powU,int pos);
	//listado de punteros a PowerUpXml
	PowerUpXml * * getListaPowerUp();
	int getCanPows();
	
	void toString(TCadena1000 cadena);
};

#endif //_ESCENARIOXML_H_
