#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_

class Observador {

public:
	Observador() { };
	virtual void actualizar(int argc, void* argv[]) = 0;
	virtual ~Observador() { };

};

#endif /* OBSERVADOR_H_ */

