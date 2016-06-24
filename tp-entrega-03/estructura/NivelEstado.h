#ifndef _NIVELESTADO_H_
#define _NIVELESTADO_H_

#include <iostream>
#include "ObjetoItem.h"
#include "GrupoItems.h"
using namespace std;

class NivelEstado
{
public:
	GrupoItems * defaultGroup;
public:
	NivelEstado();
	virtual ~NivelEstado();
	virtual void create();
	ObjetoItem * add(ObjetoItem * arg1);
	void preProcess();
	virtual void update();
	void render();
	void postProcess();
	void destroy();
};

#endif //_NIVELESTADO_H_
