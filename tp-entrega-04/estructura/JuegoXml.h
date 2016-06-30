#ifndef _JUEGOXML_H_
#define _JUEGOXML_H_

#include <iostream>
#include "Escenario.h"
using namespace std;

class JuegoXml
{
public:
	Escenario * nivel_actual;
	int _temp;
	bool _loaded;
	Escenario *lista_niveles[10];
	int canLevels;
	int last_level;
private:
	static JuegoXml* instance;	
	JuegoXml();	
public:
	static JuegoXml* getInstance();
	virtual ~JuegoXml();
	int get_levels();
	void set_levels(int arg1);
	void load();
};

#endif //_JUEGOXML_H_
