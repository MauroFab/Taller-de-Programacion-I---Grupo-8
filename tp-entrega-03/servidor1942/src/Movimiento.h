#pragma once

#include "../../common/Evento.h"

class Movimiento {

public:
	Movimiento(void);
	virtual ~Movimiento(void);
	virtual bool hayQueResponderAEventoExterno();
	virtual int getVelocidadX();
	virtual int getVelocidadY();
};

