#include "JuegoXml.h"

JuegoXml* JuegoXml::instance = NULL;

JuegoXml* JuegoXml::getInstance() {
	if(instance == NULL){
        instance = new JuegoXml();
    }
    return instance;
}

JuegoXml::JuegoXml()
{
	_loaded = false;
	nivel_actual = NULL;
	last_level = 0;
	//buscar niveles
	//se cargan 11
	for (int i = 0; i < 11; i++) {
		Escenario * nivel_x = new Escenario();
		this->lista_niveles[i] =nivel_x;
	}	
}

JuegoXml::~JuegoXml()
{
}
int JuegoXml::get_levels() {
	if (this->_loaded) {
		return this->last_level;
	}
	return this->_temp;
}
void JuegoXml::set_levels(int arg1) {
	if (this->_loaded) {
		this->last_level = arg1;
	} else {
		this->_temp = arg1;
	}
	return;
}

void JuegoXml::load() {
	this->_loaded = true;
	if (this->_loaded && this->last_level == 0) {
		this->last_level = 1;
	}
	nivel_actual = this->lista_niveles[this->last_level];
	return;
}
