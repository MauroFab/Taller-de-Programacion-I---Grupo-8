#include "AvionModel.h"

AvionModel::AvionModel()
{
	this->id = -1;
	this->velAvion = 0;
}
AvionModel::AvionModel(AvionXml * avionXml){
	this->id = avionXml->getId();
	this->velAvion = avionXml->getVelAvion();
}
AvionModel::~AvionModel()
{
}
