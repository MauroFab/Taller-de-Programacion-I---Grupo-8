#include "AsignadorDeUsuarios.h"

AsignadorDeUsuarios::AsignadorDeUsuarios(int usuariosMaximos){
	cantidadMaximaDeUsuarios = usuariosMaximos;
	cantidadDeUsuariosActuales = 0;
	colaDeMensajesDeUsuario = new std::queue<EstadoAvionXml*>[usuariosMaximos];
	estaTomadaLaId = new bool[usuariosMaximos];
	for(int i = 0; i < usuariosMaximos; i++){
		estaTomadaLaId[i] = false;
	}
}


AsignadorDeUsuarios::~AsignadorDeUsuarios(void)
{
	delete [] colaDeMensajesDeUsuario;
	delete [] estaTomadaLaId;
	std::list<Usuario*>::iterator it;

	for (it = usuarios.begin(); it != usuarios.end(); it++) {
		delete(*it);
	}
}


bool AsignadorDeUsuarios::puedoTenerMasUsuarios(void)
{
	return (cantidadDeUsuariosActuales < cantidadMaximaDeUsuarios);
}

bool AsignadorDeUsuarios::nombreDeUsuarioExistente(string nombreDeUsuario){

	std::list<Usuario*>::iterator it;

	for (it = usuarios.begin(); it != usuarios.end(); it++) {
		
		if( nombreDeUsuario.compare((*it)->nombreDeUsuario) == 0)
			return true;
	}

	return false;
}

bool AsignadorDeUsuarios::estaConectado(string nombreDeUsuario){

	std::list<Usuario*>::iterator it;

	for (it = usuarios.begin(); it != usuarios.end(); it++) {
		
		if( nombreDeUsuario.compare((*it)->nombreDeUsuario) == 0 && (*it)->conectado == true)
			return true;
	}

	return false;
}

int AsignadorDeUsuarios::reconectar(string nombreDeUsuario){

	std::list<Usuario*>::iterator it;

	for (it = usuarios.begin(); it != usuarios.end(); it++) {
		
		if( nombreDeUsuario.compare((*it)->nombreDeUsuario) == 0){
			(*it)->conectado = true;
			return (*it)->id;
		}
	}

	return -1;
}
int AsignadorDeUsuarios::obtenerUnaIdLibre(){
	int i = -1;
	bool encontreUnaIdLibre = false;
	while(!encontreUnaIdLibre && i < cantidadMaximaDeUsuarios){
		i++;
		if(!estaTomadaLaId[i]){
			encontreUnaIdLibre = true;
		}
	}
	return i;
}

int AsignadorDeUsuarios::crearUsuarioYObtenerId(string nombre){
	
	int idNuevoUsuario = -1;
	
	if (puedoTenerMasUsuarios()){

		idNuevoUsuario = obtenerUnaIdLibre();
		
		Usuario* usuario = new Usuario();

		usuario->id = idNuevoUsuario;
		usuario->nombreDeUsuario = nombre;
		usuario->conectado = true;
		usuarios.push_back(usuario);
		
		estaTomadaLaId[idNuevoUsuario] = true;
		cantidadDeUsuariosActuales++;
	}

	return idNuevoUsuario;
}

void AsignadorDeUsuarios::eliminarUsuario(int idUsuario){

	estaTomadaLaId[idUsuario] = false;
	cantidadDeUsuariosActuales--;

	// Seteo ese usuario como no conectado.
	std::list<Usuario*>::iterator it;
	for (it = usuarios.begin(); it != usuarios.end(); it++) {
		
		if((*it)->id == idUsuario)
			(*it)->conectado = false;
	}

	// Elimino la cola de mensajes para ese id
	for(int i = 0; i < colaDeMensajesDeUsuario[idUsuario].size(); i++){
		colaDeMensajesDeUsuario[idUsuario].pop();
	}
}
std::queue<EstadoAvionXml*>* AsignadorDeUsuarios::obtenerColaDeUsuario(int idUsuario){
	return &colaDeMensajesDeUsuario[idUsuario];
}

int AsignadorDeUsuarios::cantidadDeUsuarios(){
	return cantidadDeUsuariosActuales;
}