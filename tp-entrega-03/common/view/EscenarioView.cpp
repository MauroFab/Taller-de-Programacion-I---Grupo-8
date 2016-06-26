#include "EscenarioView.h"

EscenarioView::EscenarioView(FondoView* fondoV) {
	this->fondoV = fondoV;
	for (int i = 0; i < MAX_ELEMENTO_VIEW; i++) {
		this->elementosView[i] = NULL;
	}
	this->canElemenetosView = 0;
}

EscenarioView::~EscenarioView(void) {
	for (int i = 0; i < MAX_ELEMENTO_VIEW; i++) {
		delete this->elementosView[i];
	}
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