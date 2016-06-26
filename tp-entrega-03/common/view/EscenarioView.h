#pragma once

#include "FondoView.h"
#include "ElementoView.h"

#define MAX_ELEMENTO_VIEW 20

class EscenarioView {

public:
	EscenarioView(FondoView* fondoV);
	virtual ~EscenarioView(void);
	void addElementoView(ElementoView* elemento);
	FondoView* getFondoView();
	ElementoView**getElementosView();
	int getCanElemV();
private:
	FondoView* fondoV;
	ElementoView* elementosView[MAX_ELEMENTO_VIEW];
	int canElemenetosView;
};

