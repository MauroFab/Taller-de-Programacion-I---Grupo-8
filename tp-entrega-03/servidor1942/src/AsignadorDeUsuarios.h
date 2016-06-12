#pragma once
#include <queue> 
#include <list>
#include "../../juego/EstadoJuego.h"
#include "../../common/Posicion.h"
using namespace std;

//Esta clase esta hecha para crear, eliminar y brindar la dirección a las colas de cada usuario (Cliente que se le acepto la conexion)
struct Usuario {
	string nombreDeUsuario;
	bool estaAsignado;
	bool estaConectado;
	std::queue<EstadoJuego*>* colaDeMensajesDeUsuario;
	Posicion* posicion;
};

class AsignadorDeUsuarios
{
public:
	AsignadorDeUsuarios(int usuariosMaximos);
    ~AsignadorDeUsuarios();
	bool elServidorEstaLleno();
	int crearUsuarioYObtenerId(string usuario);
	void eliminarUsuario(int idUsuario);
	int cantidadDeUsuarios();
	//No tratar de liberar la memoria de la cola pedida, simplemente llamar a eliminarUsuario(int idUsuario) al final
	std::queue<EstadoJuego*>* obtenerColaDeUsuario(int idUsuario);
	int cantidadDeUsuariosActuales;
	bool nombreDeUsuarioExistente(string nombreDeUsuario);
	bool estaConectado(string nombreDeUsuario);
	bool estaConectado(int id);
	int reconectar(string nombreDeUsuario);
	void desconectarUsuario(int idUsuario);
	int getCantidadMaximaDeUsuarios();
	Posicion* getPosicionDeUsuario(int idUsuario);
	void setPosicionAUsuario(int idUsuario, Posicion pos);
	bool puedoTenerUsuariosNuevos();
private:
	
	Usuario* usuario;
	int idUsuarioLlamado(string nombre);
	int cantidadMaximaDeUsuarios;
	int obtenerUnaIdLibre();
};

