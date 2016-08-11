#ifndef _BALAMODEL_H_
#define _BALAMODEL_H_
/* @autor cbenez
 */
 #include "../xml/AvionXml.h"
class BalaModel
{
//private:
public:
	int id;
	int velBala;
public:
	BalaModel();
	BalaModel(const BalaModel& b):id(b.id),velBala(b.velBala){};
	void BalaModel::operator=(const BalaModel &b){this->id=b.id; this->velBala=b.velBala;};
	BalaModel(AvionXml * avionXml);
	virtual ~BalaModel();
};

#endif //_BALAMODEL_H_
