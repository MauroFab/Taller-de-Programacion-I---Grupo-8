#include "EscenarioView.h"

EscenarioView::EscenarioView(FondoView* fondoV) {
	this->fondoV = fondoV;

	for (int i = 0; i < MAX_ELEMENTO_VIEW; i++) {
		this->elementosView[i] = NULL;
	}
	this->canElemenetosView = 0;

	for(int i = 0; i < MAX_ENEMIGO_VIEW; i++){
		this->enemigosView[i] = NULL;
	}
	this->canEnemigoV = 0;
}

EscenarioView::~EscenarioView(void) {
	for (int i = 0; i < MAX_ELEMENTO_VIEW; i++) {
		delete this->elementosView[i];
	}
	//liberar enemigos de la vista
	for(int i = 0; i < MAX_ENEMIGO_VIEW; i++){
		delete this->enemigosView[i];
	}
	this->canEnemigoV = 0;
}

void EscenarioView::addElementoView(ElementoView* elemento) {
	this->elementosView[this->canElemenetosView] = elemento;
	this->canElemenetosView++;
}

FondoView* EscenarioView::getFondoView() {
	return this->fondoV;
}

ElementoView**EscenarioView::getElementosView() {
	return this->elementosView;
}

int EscenarioView::getCanElemV() {
	return this->canElemenetosView;
}

void EscenarioView::addAvionEnemigoView(AvionEnemigoView* avionE) {
	this->enemigosView[this->canEnemigoV] = avionE;
	this->canEnemigoV++;
}

AvionEnemigoView**EscenarioView::getAvionesEnemigosView() {
	return this->enemigosView;
}

int EscenarioView::getCanEnemigosV() {
	return this->canEnemigoV;
}