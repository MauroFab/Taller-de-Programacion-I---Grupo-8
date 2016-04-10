#include "AsignadorDeUsuarios.h"


AsignadorDeUsuarios::AsignadorDeUsuarios(int usuariosMaximos){
	cantidadMaximaDeUsuarios = usuariosMaximos;
	cantidadDeUsuariosActuales = 0;
	colaDeMensajesDeUsuario = new std::queue<char*>[usuariosMaximos];
	estaTomadaLaId = new bool[usuariosMaximos];
	for(int i = 0; i < usuariosMaximos; i++){
		estaTomadaLaId[i] = false;
	}
}


AsignadorDeUsuarios::~AsignadorDeUsuarios(void)
{
	delete [] colaDeMensajesDeUsuario;
	delete [] estaTomadaLaId;
}

bool AsignadorDeUsuarios::puedoTenerMasUsuarios(void)
{
	return (cantidadDeUsuariosActuales < cantidadMaximaDeUsuarios);
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

int AsignadorDeUsuarios::crearUsuarioYObtenerId(){
	int idNuevoUsuario = -1;
	if (puedoTenerMasUsuarios()){
		idNuevoUsuario = obtenerUnaIdLibre();
		estaTomadaLaId[idNuevoUsuario] = true;
		cantidadDeUsuariosActuales++;
	}
	return idNuevoUsuario;
}
void AsignadorDeUsuarios::eliminarUsuario(int idUsuario){
	estaTomadaLaId[idUsuario] = false;
	cantidadDeUsuariosActuales--;
	for(int i = 0; i < colaDeMensajesDeUsuario[idUsuario].size(); i++){
		colaDeMensajesDeUsuario[idUsuario].pop();
	}
}

std::queue<char*>* AsignadorDeUsuarios::obtenerColaDeUsuario(int idUsuario){
	return &colaDeMensajesDeUsuario[idUsuario];
}

int AsignadorDeUsuarios::cantidadDeUsuarios(){
	return cantidadDeUsuariosActuales;
}