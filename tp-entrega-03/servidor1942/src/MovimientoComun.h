#pragma once

#include "Movimiento.h"

class MovimientoComun : public Movimiento {

public:
	MovimientoComun(void);
	virtual ~MovimientoComun(void);
	bool hayQueResponderAEventoExterno();
	int getVelocidadX();
	int getVelocidadY();
};

