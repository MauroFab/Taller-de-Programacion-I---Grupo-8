#pragma once

#include <list>
#include "ModoDeJuego.h"

using namespace std;

class ModoColaboracion : public ModoDeJuego {

public:
	ModoColaboracion(void);
	virtual ~ModoColaboracion(void);
	char* toString();
	char* getDisponibilidadToString();
	bool seJuegaPorEquipos();
	bool hayDisponibilidad();
	void asociarUsuarioAEquipo(int idUsuario, char* equipo);
	void agregarUsuario(int idUsuario);
private:
	std::list<int> usuarios;
};

