#ifndef _AVIONMODEL_H_
#define _AVIONMODEL_H_
/* @autor cbenez
 */
 #include "../xml/AvionXml.h"
class AvionModel
{
//private:	
public:
	int id;
	int velAvion;
public:
	AvionModel();
	AvionModel(AvionXml * avionXml);
	virtual ~AvionModel();
};

#endif //_AVIONMODEL_H_
