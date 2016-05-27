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
	BalaModel(AvionXml * avionXml);
	virtual ~BalaModel();
};

#endif //_BALAMODEL_H_
