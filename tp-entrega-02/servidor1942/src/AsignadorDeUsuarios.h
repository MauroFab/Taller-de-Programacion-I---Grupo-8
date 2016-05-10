#pragma once
#include <queue> 
#include <list>
#include "../../common/xml/MovimientoXml.h"
using namespace std;

//Esta clase esta hecha para crear, eliminar y brindar la dirección a las colas de cada usuario (Cliente que se le acepto la conexion)

class AsignadorDeUsuarios
{
public:
	AsignadorDeUsuarios(int usuariosMaximos);
    ~AsignadorDeUsuarios();
	bool puedoTenerMasUsuarios();
	int crearUsuarioYObtenerId();
	void eliminarUsuario(int idUsuario);
	int cantidadDeUsuarios();
	//No tratar de liberar la memoria de la cola pedida, simplemente llamar a eliminarUsuario(int idUsuario) al final
	std::queue<MovimientoXml*>* obtenerColaDeUsuario(int idUsuario);
	int cantidadDeUsuariosActuales;
private:
	std::queue<MovimientoXml*>* colaDeMensajesDeUsuario;
	bool* estaTomadaLaId;
	int cantidadMaximaDeUsuarios;
	int obtenerUnaIdLibre();
};

