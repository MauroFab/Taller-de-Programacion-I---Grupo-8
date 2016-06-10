#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_
#include "../../common/Evento.h"
class Observador {

public:
	Observador() { };
	virtual int actualizar(Evento* evento) = 0;
	virtual ~Observador() { };

};

#endif /* OBSERVADOR_H_ */

