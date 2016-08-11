#ifndef _AVIONMODEL_H_
#define _AVIONMODEL_H_
/* @autor cbenez
 */
#include "../xml/AvionXml.h"

class AvionModel {

public:
	int id;
	int velAvion;
public:
	AvionModel();
	AvionModel(const AvionModel& b):id(b.id),velAvion(b.velAvion){};
	void AvionModel::operator=(const AvionModel &b){this->id=b.id; this->velAvion=b.velAvion;};
	AvionModel(AvionXml * avionXml);
	~AvionModel();
};

#endif //_AVIONMODEL_H_
