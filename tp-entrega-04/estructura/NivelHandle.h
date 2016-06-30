#ifndef _NIVELHANDLE_H_
#define _NIVELHANDLE_H_

#include "JuegoXml.h"
#include "JuegoContainer.h"

class NivelHandle
{
public:
	int total_levels;
	int current_level;
public:
	NivelHandle();
	virtual ~NivelHandle();
	void play_next();
	void start_current_level();
	void load_level_data();

};

#endif //_NIVELHANDLE_H_
