#include "xml\EstadoProyectilXml.h"
#include "xml\EstadoAvionXml.h"
#include "xml\MensajeXml.h"
#include "MensajeFactory.h" 

Mensaje* MensajeFactory::crear(int mensaje){
	//TODO: implementar
	return NULL;
}

Mensaje* MensajeFactory::crear(double mensaje){
	//TODO: implementar
	return NULL;
}

Mensaje* MensajeFactory::crear(char mensaje){
	//TODO: implementar
	return NULL;
}

Mensaje* MensajeFactory::crear(std::string mensaje){

	MensajeXml* msj = new MensajeXml();
	msj->setValor((char*)mensaje.c_str(), strlen(mensaje.c_str()));
	msj->setTipoValor(TIPO_STRING);
	msj->calculateSizeBytes();

	return msj;
}

Mensaje* MensajeFactory::crear(EstadoAvion* estado){

	EstadoAvionXml* msj = new EstadoAvionXml(estado->getId(), estado->getFrame(), estado->getPosX(), estado->getPosY());
	
	std::list<EstadoProyectil*>::iterator it;
	std::list<EstadoProyectil*> listaP = estado->getEstadosProyectiles();

	for (it = listaP.begin(); it != listaP.end(); it++) {
		msj->agregarEstadoProyectil(new EstadoProyectilXml((*it)->getFrame(),(*it)->getPosX(), (*it)->getPosY()));
	}

	return msj;
}

