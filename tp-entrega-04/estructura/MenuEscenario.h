#ifndef _MENUESCENARIO_H_
#define _MENUESCENARIO_H_

#include "Escenario.h"

class MenuEscenario : public Escenario
{
public:
	MenuEscenario();
	virtual ~MenuEscenario();
	void create();
	void update();
};

#endif //_MENUESCENARIO_H_
