#ifndef _BALA_H_
#define _BALA_H_

#include "ObjetoItem.h"

class Bala : public ObjetoItem
{
protected:
	int idOwner;
  
    int life_time;
public:
	Bala();
	virtual ~Bala();
	virtual void update();
	virtual void kill();
    void render();
};

#endif //_BALA_H_
