#pragma once

#include "FondoView.h"
#include "ElementoView.h"
#include "AvionEnemigoView.h"

#define MAX_ELEMENTO_VIEW 20
#define MAX_ENEMIGO_VIEW 5

class EscenarioView {

public:
	EscenarioView(FondoView* fondoV);
	virtual ~EscenarioView(void);
	void addElementoView(ElementoView* elemento);
	void addAvionEnemigoView(AvionEnemigoView* avionE);
	FondoView* getFondoView();
	ElementoView**getElementosView();
	AvionEnemigoView**getAvionesEnemigosView();
	int getCanElemV();
	int getCanEnemigosV();
private:
	FondoView* fondoV;
	ElementoView* elementosView[MAX_ELEMENTO_VIEW];
	AvionEnemigoView * enemigosView[MAX_ENEMIGO_VIEW];
	int canEnemigoV;
	int canElemenetosView;
};

