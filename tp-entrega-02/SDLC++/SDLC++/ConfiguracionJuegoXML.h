#pragma once
#include "Constantes.h"
#include "ConfiguracionAvionXML.h"
#include "ConfiguracionProyectilXML.h"

class ConfiguracionJuegoXML {

public:

	static ConfiguracionJuegoXML* getInstance();

	virtual ~ConfiguracionJuegoXML(void);

	void setCaracteristicasMapa(std::string fondo, std::string isla, int tamanioMaximoFondo);
	void setCaracteristicasAvion(std::string avion, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad);
	void setCaracteristicasProyectil(std::string proyectil, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad);

	ConfiguracionAvionXML* getConfiguracionAvion();
	ConfiguracionProyectilXML* getConfiguracionProyectil();
	std::string getPathFondo();
	std::string getPathIsla();
	int getTamanioMaximoFondo();

private:

	ConfiguracionJuegoXML(void);

	static bool instanceFlag;
	static ConfiguracionJuegoXML* instance;

	std::string pathImagenFondo;
	std::string pathImagenIsla;
	int tamanioMaximoFondo;

	ConfiguracionAvionXML* configAvion;
	ConfiguracionProyectilXML* configProyectil;
};

