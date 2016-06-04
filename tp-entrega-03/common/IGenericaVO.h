#ifndef _IGENERICAVO_H_
#define _IGENERICAVO_H_
/* @autor sabris
 * interface generica para los VO (Value Object), se refiere a los objetos que
 * contienen los datos del modelo
*/

typedef char TCadena1000[1000];

typedef struct posicion{
                int coorX;
                int coorY;
               }TPosicion;

class IGenericaVO
{
public:
	IGenericaVO(){};
	//virtual ~IGenericaVO(){};
	//carga el contenido del objeto VO
	virtual void toString(TCadena1000 cadena) = 0;
	//retorna la cantidad de bytes a transmitirse/recibirse, luego de codificar/decodificar
	virtual int getSizeBytes() = 0;
	//calcula y guarda la cantidad de bytes a transmitirse/recibirse, luego de codificar/decodificar
	virtual void calculateSizeBytes() = 0;
//TODO no eliminar estos comentarios	
	//setea el ID del objeto que sera unico para su tipo, ejemplo avion 1,2,3.. elemento 1,2,3
//	virtual void setId(int id) = 0;
	//obtiene el ID del objeto que sera unico para su tipo, ejemplo avion 1,2,3.. elemento 1,2,3
//	virtual int getId() = 0;
};

#endif //_IGENERICAVO_H_
