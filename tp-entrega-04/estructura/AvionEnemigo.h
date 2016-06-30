#ifndef _AVIONENEMIGO_H_
#define _AVIONENEMIGO_H_
#define TIPO_AVION_BIG	1	
#define TIPO_AVION_FORMACION	2	
#define TIPO_AVION_MIDDLE	3	
#define TIPO_AVION_MINI	4	

#include <iostream>

#include "../common/IGenericaVO.h"
#include "ObjetoItem.h"
#include "BalaEnemigo.h"
using namespace std;
//forward declaration. NO usar si no se conoce el uso
class PowerUp;

class AvionEnemigo : public ObjetoItem
{
protected:
	int energiaInicial;//cantidad de disparos que soporta
	int energia;
	int puntos;
	TPosicion trayectoria;
	bool bEnMuerte;
	bool bUnaVez;
public:
	AvionEnemigo();
	AvionEnemigo(int p_x,int p_y);
	virtual ~AvionEnemigo();
	int givePuntos();
	void reduceEnergia(int deltaEnergia);
	virtual BalaEnemigo * disparar();
	virtual void update(); 
};

#endif //_AVIONENEMIGO_H_
