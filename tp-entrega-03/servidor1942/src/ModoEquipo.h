#pragma once

#include <list>
#include "ModoDeJuego.h"

using namespace std;

class ModoEquipo : public ModoDeJuego {

public:
	ModoEquipo(int cantidadMaximaClientes);
	virtual ~ModoEquipo(void);
	char* toString();
	char* getDisponibilidadToString();
	bool seJuegaPorEquipos();
	bool hayDisponibilidad();
	void asociarUsuarioAEquipo(int idUsuario, char* equipo);
	void agregarUsuario(int idUsuario);
private:
	bool hayDisponibilidadEquipoUno();
	bool hayDisponibilidadEquipoDos();
	int cantidadClientes;
	std::list<int> equipo1;
	std::list<int> equipo2;
};

