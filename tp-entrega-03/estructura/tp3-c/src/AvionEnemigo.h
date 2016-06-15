#ifndef _AVIONENEMIGO_H_
#define _AVIONENEMIGO_H_
#define TIPO_AVION_BIG	1	
#define TIPO_AVION_FORMACION	2	
#define TIPO_AVION_MIDDLE	3	
#define TIPO_AVION_MINI	4	
//forward declaration
class PowerUp;

class AvionEnemigo
{
protected:
	int energiaInicial;//cantidad de disparos que soporta
	int energia;
	int valorPuntaje;
	int trayectoria;
public:
	AvionEnemigo();
	virtual ~AvionEnemigo();
	int givePuntos();
	void reduceEnergia(int deltaEnergia);
	void disparar();
};

#endif //_AVIONENEMIGO_H_
