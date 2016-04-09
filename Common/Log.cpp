#include "Log.h"
#include "StringUtil.h"

#include <sstream>
#include <algorithm>

bool Log::instanceFlag = false;
Log* Log::single = NULL;

const char* Log::textoNiveles[] = { "ERROR", "WARN", "INFO", "DEBUG" };

Log::Log(){

	mut = SDL_CreateMutex();

	// TODO: Obtener el nombre del archivo y los niveles de log de un archivo de configuracion.
	nivelesConfigurados.push_front(0);
	nivelesConfigurados.push_front(1);
	nivelesConfigurados.push_front(2);
	nivelesConfigurados.push_front(3);

	ostringstream os;

	os << "Logs/"<< StringUtil::obtenerFechaAAAAMMDD(NULL) << "_TP1.log";

	this->archivoLog.open(os.str().c_str(), std::ofstream::out | std::ofstream::app);
}

Log::~Log(){

	this->archivoLog.close();
	SDL_DestroyMutex(mut);
	instanceFlag = false;
}

Log* Log::getInstance(){
    
	if(! instanceFlag){
        single = new Log();
        instanceFlag = true;
        return single;
    }
    else{
        return single;
    }
}

void Log::debug(string mensaje){
	escribirMensaje(NivelLog::LOG_DEBUG, mensaje);
}

void Log::info(string mensaje){
	escribirMensaje(NivelLog::LOG_INFORMACION, mensaje);
}

void Log::warn(string mensaje){
	escribirMensaje(NivelLog::LOG_ADVERTENCIA, mensaje);
}

void Log::error(string mensaje){
	escribirMensaje(NivelLog::LOG_ERROR, mensaje);
}

void Log:: escribirFecha(){

	this->archivoLog << "[" << StringUtil::obtenerFechaDDMMAAAAmmss() << "]";
}

void Log::escribirMensaje(NivelLog nivel, string mensaje){

	bool loggearNivel = (std::find(this->nivelesConfigurados.begin(), this->nivelesConfigurados.end(), nivel) != this->nivelesConfigurados.end());
	
	if(!loggearNivel)
		return;

	SDL_mutexP(mut);

	this->escribirFecha();
	this->archivoLog << textoNiveles[nivel] << ": ";
	this->archivoLog << mensaje << endl;

	SDL_mutexV(mut);
}
