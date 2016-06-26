#pragma once

#include <string>

using namespace std;

class ModoDeJuego {

public:
	ModoDeJuego(void);
	virtual ~ModoDeJuego(void);
	virtual char* toString();
	virtual char* getDisponibilidadToString();
	virtual bool seJuegaPorEquipos();
	virtual bool hayDisponibilidad();
	virtual void asociarUsuarioAEquipo(int idUsuario, char* equipo);
	virtual void agregarUsuario(int idUsuario);
};

