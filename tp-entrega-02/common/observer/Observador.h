#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_

class Observador {

public:
	Observador() { };
	virtual void actualizar(void* argv[]) = 0;
	virtual ~Observador() { };

};

#endif /* OBSERVADOR_H_ */

