#include "ElementoModel.h"

ElementoModel::ElementoModel()
{
	this->posicion.coorX = -1;
	this->posicion.coorY = -1;
}

ElementoModel::ElementoModel(ElementoXml * elementoXml)
{
	this->posicion.coorX = elementoXml->getPosicion().coorX;
	this->posicion.coorY = elementoXml->getPosicion().coorY;
}

ElementoModel::~ElementoModel()
{
}
