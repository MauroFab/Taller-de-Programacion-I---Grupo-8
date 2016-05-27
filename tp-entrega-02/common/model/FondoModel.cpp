#include "FondoModel.h"

FondoModel::FondoModel()
{
	this->id = -1;
	this->posicionY = 0;
}
FondoModel::FondoModel(FondoXml * fondoXml){
	this->id = fondoXml->getId();
	this->posicionY = 0;
}
FondoModel::~FondoModel()
{
}
