#ifndef _AVIONENEMIGOMODEL_H_
#define _AVIONENEMIGOMODEL_H_

 #include "../xml/AvionEnemigoXml.h"
class AvionEnemigoModel
{
public:
	int id;
	int velAvion;
	int tipo;
public:
	AvionEnemigoModel();
	AvionEnemigoModel(AvionEnemigoXml *  avionEnemigoXml);
	virtual ~AvionEnemigoModel();
};

#endif //_AVIONENEMIGOMODEL_H_
