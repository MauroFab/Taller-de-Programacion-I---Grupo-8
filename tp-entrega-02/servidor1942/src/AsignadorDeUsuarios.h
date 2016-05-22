#pragma once
#include <queue> 
#include <list>
#include "../../common/xml/EstadoAvionXml.h"
using namespace std;

//Esta clase esta hecha para crear, eliminar y brindar la dirección a las colas de cada usuario (Cliente que se le acepto la conexion)
struct Usuario {
	int id;
	string nombreDeUsuario;
	bool conectado;
};
class AsignadorDeUsuarios
{
public:
	AsignadorDeUsuarios(int usuariosMaximos);
    ~AsignadorDeUsuarios();
	bool puedoTenerMasUsuarios();
	int crearUsuarioYObtenerId(string usuario);
	void eliminarUsuario(int idUsuario);
	int cantidadDeUsuarios();
	//No tratar de liberar la memoria de la cola pedida, simplemente llamar a eliminarUsuario(int idUsuario) al final
	std::queue<EstadoAvionXml*>* obtenerColaDeUsuario(int idUsuario);
	int cantidadDeUsuariosActuales;
	bool nombreDeUsuarioExistente(string nombreDeUsuario);
	bool estaConectado(string nombreDeUsuario);
	int reconectar(string nombreDeUsuario);
private:
	std::queue<EstadoAvionXml*>* colaDeMensajesDeUsuario;
	bool* estaTomadaLaId;
	std::list<Usuario*> usuarios;
	int cantidadMaximaDeUsuarios;
	int obtenerUnaIdLibre();
};

