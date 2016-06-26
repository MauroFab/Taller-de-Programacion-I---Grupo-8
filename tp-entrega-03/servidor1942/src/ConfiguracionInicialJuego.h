#pragma once

#include "../../common/xml/ServidorXml.h"
#include "ModoDeJuego.h"
#include "ModoColaboracion.h"
#include "ModoEquipo.h"

class ConfiguracionInicialJuego {

public:
	static ConfiguracionInicialJuego* getInstance();
	virtual ~ConfiguracionInicialJuego(void);

	void inicializar(ServidorXml* servidorXml);
	char* getModoDeJuego();
	char* getDisponibilidad();
	bool seJuegaPorEquipos();
	bool hayDisponibilidad();
	void asociarUsuarioAEquipo(int idUsuario, char* equipo);
	void agregarUsuario(int idUsuario);
private:
	ConfiguracionInicialJuego(void);
	static ConfiguracionInicialJuego* instance;
	ModoDeJuego* modoDeJuego;
};

