#include "AvionModel.h"

AvionModel::AvionModel()
{
	this->velAvion = 0;
}
AvionModel::AvionModel(AvionXml * avionXml){
	this->velAvion = avionXml->getVelAvion();
}
AvionModel::~AvionModel()
{
}
