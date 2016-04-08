#pragma once
#include <queue> 
#include <list>

//Esta clase esta hecha para crear, eliminar y brindar la dirección a las colas de cada usuario (Cliente que se le acepto la conexion)

class AsignadorDeUsuarios
{
public:
	AsignadorDeUsuarios(int usuariosMaximos);
    ~AsignadorDeUsuarios();
	bool puedoTenerMasUsuarios();
	int crearUsuarioYObtenerId();
	void eliminarUsuario(int idUsuario);
	//No tratar de liberar la memoria de la cola pedida, simplemente llamar a eliminarUsuario(int idUsuario) al final
	std::queue<char*>* obtenerColaDeUsuario(int idUsuario);
private:
	std::queue<char*>* colaDeMensajesDeUsuario;
	bool* estaTomadaLaId;
	int cantidadMaximaDeUsuarios;
	int cantidadDeUsuariosActuales;
	int obtenerUnaIdLibre();
};

