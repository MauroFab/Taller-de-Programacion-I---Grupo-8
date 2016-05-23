#include "ConfiguracionJuegoXML.h"

bool ConfiguracionJuegoXML::instanceFlag = false;
ConfiguracionJuegoXML* ConfiguracionJuegoXML::instance = NULL;

ConfiguracionJuegoXML::ConfiguracionJuegoXML(void) {
}

ConfiguracionJuegoXML::~ConfiguracionJuegoXML(void) {
}

ConfiguracionJuegoXML* ConfiguracionJuegoXML::getInstance() {
	
	if(!instanceFlag){
        instance = new ConfiguracionJuegoXML();
        instanceFlag = true;
    }
    return instance;
}

void ConfiguracionJuegoXML::setCaracteristicasMapa(std::string fondo, int tamanioMaximoMapa) {
	pathImagenFondo = fondo;
	tamanioMaximoFondo = tamanioMaximoMapa;
}

void ConfiguracionJuegoXML::setCaracteristicasProyectil(std::string proyectil, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad) {

	configProyectil = new ConfiguracionProyectilXML(proyectil, cantFotogramas, anchoFotograma, altoFotograma, velocidad);
}


ConfiguracionProyectilXML* ConfiguracionJuegoXML::getConfiguracionProyectil() {
	return configProyectil;
}

std::string ConfiguracionJuegoXML::getPathFondo() {
	return pathImagenFondo;
}

int ConfiguracionJuegoXML::getTamanioMaximoFondo() {
	return tamanioMaximoFondo;
}