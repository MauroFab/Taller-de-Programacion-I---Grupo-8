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

void ConfiguracionJuegoXML::setBalaView(BalaView * balaView){
	this->balaView = balaView;
}
