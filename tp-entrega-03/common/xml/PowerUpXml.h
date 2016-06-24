#ifndef _POWERUPXML_H_
#define _POWERUPXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "../IGenericaVO.h"

#define P_TIPO_MUERTE		1
#define P_TIPO_AMETRALLADORA	2
#define P_TIPO_PUNTOS		3

#define S_TIPO_MUERTE			"muerte"
#define S_TIPO_AMETRALLADORA	"bala"
#define S_TIPO_PUNTOS			"puntos"

class PowerUpXml : public IGenericaVO
{
private:
	int sizeBytes;
	int id;
	int idSprite;//spriteId:id numerico del sprite
	char * strIdSprite;//spriteId:cadena q contiene el nombre
	TPosicion posicion;
	int tipo;
public:
	PowerUpXml();
	PowerUpXml(int idSprite,char * strIdSprite,int coorX,int coorY,int tipo);
	PowerUpXml(const PowerUpXml&powerUp);
	virtual ~PowerUpXml();
	
	int getSizeBytes();
	void calculateSizeBytes();
	void setId(int id);
	int getId();
	void setIdSprite(int idSprite);
	int getIdSprite();
	void setStrIdSprite(char * strIdSprite, int len_strIdSprite);
	char * getStrIdSprite();
	void setPosicion(TPosicion posicion);
	TPosicion getPosicion();
	void setTipo(int tipo);
	int getTipo();	
    PowerUpXml & operator = (const PowerUpXml & source);
	void toString(TCadena1000 cadena);
};

#endif //_POWERUPXML_H_
