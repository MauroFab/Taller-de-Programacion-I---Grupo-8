#include "Log.h"
#include "StringUtil.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <exception>

bool Log::instanceFlag = false;
Log* Log::single = NULL;

Log::Log(){

	mut = SDL_CreateMutex();

	cargarConfiguracion();

	ostringstream os;

	os << "log/" << StringUtil::obtenerFechaAAAAMMDD(NULL) << nombreLog << ".log";

	this->archivoLog.open(os.str().c_str(), std::ofstream::out | std::ofstream::app);
	this->archivoLog <<  endl;
}

void Log::cargarConfiguracion(){

	string defaultValues[] = {ERROR, WARN, INFO, DEBUG};

	try{

		ifstream archivoConfiguracion("config/Log.ini", std::ifstream::in);

		if(archivoConfiguracion){

			string linea;

			while(!archivoConfiguracion.eof()){

				getline(archivoConfiguracion, linea);

				// Cuando encuentro la key de configuracion la remuevo y tambien los espaciones en blanco
				if(linea.find("NOMBRE") != string::npos){

					linea = StringUtil::reemplazarString(linea,"NOMBRE_ARCHIVO", "");
					linea = StringUtil::reemplazarString(linea,"=", "");

					nombreLog = StringUtil::reemplazarString(linea," ", "");
				}
				else if(linea.find("NIVEL_LOG") != string::npos){

					linea = StringUtil::reemplazarString(linea,"NIVEL_LOG", "");
					linea = StringUtil::reemplazarString(linea,"=", "");
					linea = StringUtil::reemplazarString(linea," ", "");

					// Separo los niveles 
					char* tokens = strtok(&linea[0],"|");

					while(tokens != NULL)
					{
						nivelesConfigurados.push_back(tokens);
						tokens = strtok(NULL, "|");
					}
				}
			}

			archivoConfiguracion.close();
		}
	}
	catch(exception& ex){
		 cout << "[ERROR] Configuracion LOG: " << ex.what();
	}

	// Cargo valores default en caso que no exista configuracion
	if(nombreLog.empty())
		nombreLog = "TP";
	
	if(nivelesConfigurados.empty()){

		for (int i=0; i<5 ; ++i)
			nivelesConfigurados.push_back(defaultValues[i]);
	}
}

Log::~Log(){

	this->archivoLog.close();
	SDL_DestroyMutex(mut);
	instanceFlag = false;
}

Log* Log::getInstance(){
    
	if(!instanceFlag){
        single = new Log();
        instanceFlag = true;
        return single;
    }
    else{
        return single;
    }
}

void Log::debug(string mensaje){
	escribirMensaje(DEBUG, mensaje);
}

void Log::info(string mensaje){
	escribirMensaje(INFO, mensaje);
}

void Log::warn(string mensaje){
	escribirMensaje(WARN, mensaje);
}

void Log::error(string mensaje){
	escribirMensaje(ERROR, mensaje);
}

void Log::escribirMensaje(string nivel, string mensaje){

	bool loggearNivel = (std::find(this->nivelesConfigurados.begin(), this->nivelesConfigurados.end(), nivel) != this->nivelesConfigurados.end());
	
	if(!loggearNivel)
		return;

	SDL_mutexP(mut);

	this->archivoLog << "[" << StringUtil::obtenerFechaDDMMAAAAmmss() << "]" << nivel << ": " << mensaje << endl;

	SDL_mutexV(mut);
}

