#include "Log.h"
#include "StringUtil.h"

#include <sstream>


bool Log::instanceFlag = false;
Log* Log::single = NULL;

const char* Log::tipos[] = { "ERROR", "INFORMACION", "DEBUG" };

Log::Log(){

	ostringstream os;

	os << "Logs/"<< StringUtil::obtenerFechaAAAAMMDD(NULL) << "_TP1.log";

	this->archivoLog.open(os.str().c_str(), std::ofstream::out | std::ofstream::app);
}

Log::~Log(){

	this->archivoLog.close();
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

void Log:: escribirFecha(){

	this->archivoLog << "[" << StringUtil::obtenerFechaDDMMAAAAmmss() << "]";
}

void Log::escribirMensaje(string mensaje){

	this->escribirFecha();
	this->archivoLog << mensaje << endl;
}

void Log::escribirMensaje(LogTipo tipo, string mensaje){

	this->escribirFecha();
	this->archivoLog << tipos[tipo] << ": ";
	this->archivoLog << mensaje << endl;
}
