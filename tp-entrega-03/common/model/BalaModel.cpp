#include "BalaModel.h"

BalaModel::BalaModel()
{
	this->id = -1;
	this->velBala = 0;
}
BalaModel::BalaModel(AvionXml * avionXml)
{
	this->id = -1;
	this->velBala = avionXml->getVelBala();
}

BalaModel::~BalaModel()
{
}
