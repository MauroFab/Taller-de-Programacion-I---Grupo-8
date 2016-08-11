#include "AvionEnemigoModel.h"

AvionEnemigoModel::AvionEnemigoModel() {
	this->id = -1;
	this->velAvion = 0;
	this->tipo = -1;
}

AvionEnemigoModel::AvionEnemigoModel(AvionEnemigoXml *  avionEnemigoXml){
	this->id = avionEnemigoXml->getId();
	this->tipo = avionEnemigoXml->getTipo();
}

AvionEnemigoModel::~AvionEnemigoModel() {
}
