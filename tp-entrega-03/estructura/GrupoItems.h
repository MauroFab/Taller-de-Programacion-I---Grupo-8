#ifndef _GRUPOITEMS_H_
#define _GRUPOITEMS_H_

#include <vector>
#include <iostream>
#include "../common/IGenericaVO.h"
#include "ObjetoItem.h"
using namespace std;

class GrupoItems : public ObjetoItem
{
public:
    vector<ObjetoItem*> members;
    FPoint _last;
    bool _first;
    bool solid;

public:
	GrupoItems();
	virtual ~GrupoItems();
	ObjetoItem* add(ObjetoItem * arg1);
	ObjetoItem* add(ObjetoItem * arg1, bool arg2);
	void saveOldPosition();
	void updateMembers();
	void update();
	void renderMembers();
	void render();
	void killMembers();
	void kill();
	void destroyMembers();
	void destroy();
	
};

#endif //_GRUPOITEMS_H_
