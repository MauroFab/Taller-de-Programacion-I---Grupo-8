#include "AsignadorDeUsuarios.h"

AsignadorDeUsuarios::AsignadorDeUsuarios(int usuariosMaximos){
	cantidadMaximaDeUsuarios = usuariosMaximos;
	cantidadDeUsuariosActuales = 0;
	listUsuario = new Usuario[usuariosMaximos];
	for(int i = 0; i<usuariosMaximos; i++){
		listUsuario[i].estaConectado = false;
		listUsuario[i].estaAsignado = false;
		listUsuario[i].colaDeMensajesDeUsuario = new std::queue<EstadoJuego*>;
		listUsuario[i].posicion = new Posicion(200, 400);
	}
}


AsignadorDeUsuarios::~AsignadorDeUsuarios(void)
{
	for(int i = 0; i<cantidadMaximaDeUsuarios; i++){
		delete listUsuario[i].colaDeMensajesDeUsuario;
		delete listUsuario[i].posicion;
	}
	delete []listUsuario;
}

bool AsignadorDeUsuarios::elServidorEstaLleno(void)
{
	return (cantidadDeUsuariosActuales >= cantidadMaximaDeUsuarios);
}
bool AsignadorDeUsuarios::puedoTenerUsuariosNuevos(){
	int cantidadDeUsuariosQueSeCrearon = 0;
	for(int i = 0; i< cantidadMaximaDeUsuarios; i++){
		if(listUsuario[i].estaAsignado)
			cantidadDeUsuariosQueSeCrearon++;
	}
	return (cantidadDeUsuariosQueSeCrearon < cantidadMaximaDeUsuarios);
}

bool AsignadorDeUsuarios::isNombreUsuarioExistente(string nombreDeUsuarioRecibido){
	bool bNombreEnc = false;
	for(int i = 0; i< cantidadMaximaDeUsuarios; i++){
		if(listUsuario[i].estaAsignado && !bNombreEnc){
			bNombreEnc = (listUsuario[i].nombreDeUsuario.compare(nombreDeUsuarioRecibido) == 0);
		}
	}

	return bNombreEnc;
}

bool AsignadorDeUsuarios::estaConectado(string nombre){

	std::list<Usuario*>::iterator it;
	int idUsuario;
	idUsuario = idUsuarioLlamado(nombre);
	if(idUsuario != -1)
		return  listUsuario[idUsuario].estaConectado;
	//Si el usuario no existe devuelve falso
	return false;
}
bool AsignadorDeUsuarios::estaConectado(int id){
	return (listUsuario[id].estaConectado);
}
int AsignadorDeUsuarios::idUsuarioLlamado(string nombre){
	for(int i = 0; i< cantidadMaximaDeUsuarios; i++){
		if(listUsuario[i].nombreDeUsuario.compare(nombre) == 0){
			return(i);
		}
	}
	return -1;
}
int AsignadorDeUsuarios::reconectar(string nombreUsuario){

	std::list<Usuario*>::iterator it;
	int id;
	id = idUsuarioLlamado(nombreUsuario);
	if(id != -1){
		listUsuario[id].estaConectado = true;
		cantidadDeUsuariosActuales++;
	}
	return id;
}
int AsignadorDeUsuarios::obtenerUnaIdLibre(){
	int i = -1;
	bool encontreUnaIdLibre = false;
	while(!encontreUnaIdLibre && i < cantidadMaximaDeUsuarios){
		i++;
		encontreUnaIdLibre = !listUsuario[i].estaAsignado;
	}
	return i;
}

int AsignadorDeUsuarios::crearUsuarioYObtenerId(string nombre){
	
	int idNuevoUsuario = -1;
	
	if (!elServidorEstaLleno()){

		idNuevoUsuario = obtenerUnaIdLibre();
		listUsuario[idNuevoUsuario].estaAsignado = true;
		listUsuario[idNuevoUsuario].estaConectado = true;
		listUsuario[idNuevoUsuario].nombreDeUsuario = nombre;
		cantidadDeUsuariosActuales++;
	}

	return idNuevoUsuario;
}

void AsignadorDeUsuarios::eliminarUsuario(int idUsuario){
	while(!listUsuario[idUsuario].colaDeMensajesDeUsuario->empty()){
		listUsuario[idUsuario].colaDeMensajesDeUsuario->pop();
	}
	listUsuario[idUsuario].estaAsignado = false;
	listUsuario[idUsuario].estaConectado = false;
	cantidadDeUsuariosActuales--;
}

void AsignadorDeUsuarios::desconectarUsuario(int idUsuario){
//	int id;
	listUsuario[idUsuario].estaConectado = false;
	cantidadDeUsuariosActuales--;
	while(!listUsuario[idUsuario].colaDeMensajesDeUsuario->empty()){
		listUsuario[idUsuario].colaDeMensajesDeUsuario->pop();
	}
}
std::queue<EstadoJuego*>* AsignadorDeUsuarios::obtenerColaDeUsuario(int idUsuario){
	return listUsuario[idUsuario].colaDeMensajesDeUsuario;
}

int AsignadorDeUsuarios::cantidadDeUsuarios(){
	return cantidadDeUsuariosActuales;
}

int AsignadorDeUsuarios::getCantidadMaximaDeUsuarios(){
	return cantidadMaximaDeUsuarios;
}

Posicion* AsignadorDeUsuarios::getPosicionDeUsuario(int idUsuario) {
	return listUsuario[idUsuario].posicion;
}

void AsignadorDeUsuarios::setPosicionAUsuario(int idUsuario, Posicion pos) {

	Posicion* posicion = getPosicionDeUsuario(idUsuario);

	posicion->setPosX(pos.getPosX());
	posicion->setPosY(pos.getPosY());
}

string AsignadorDeUsuarios::getNombreDeUsuarioDeJugador(int idUsuario) {
	return this->listUsuario[idUsuario].nombreDeUsuario;
}