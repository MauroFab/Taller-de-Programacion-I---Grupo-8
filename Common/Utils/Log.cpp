#include "Log.h"
#include "StringUtil.h"

#include <time.h>
#include <sstream>


bool Log::instanceFlag = false;
Log* Log::single = NULL;

const char* Log::tipos[] = { "ERROR", "INFORMACION", "DEBUG" };

Log::Log(){

	time_t segundos = time(NULL);
    tm* d = localtime(&segundos);

	ostringstream os;
	os << "Logs/"<< (d->tm_year + 1900) << (d->tm_mon + 1) << (d->tm_mday) << "_Log.log";

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

	time_t segundos = time(NULL);
    tm* d = localtime(&segundos);

	this->archivoLog << "[" << d->tm_mday << "/" << (d->tm_mon + 1) << "/" << (1900 + d->tm_year);
	this->archivoLog << "-" << d->tm_hour << ":" << d->tm_min << ":" << d->tm_sec << "]";

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
