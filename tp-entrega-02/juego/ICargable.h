#ifndef _ICARGABLE_H_
#define _ICARGABLE_H_
/* @autor sabris
 * Interface para cargar los objetos del Modelo con los objetos XML que vienen desde el servidor
 * dado que cada objeto XML implementa IGenericaVO, se cargara los ICargable con IGenericaVO y luego seran
 * casteados segun sea necesario
*/
#include "../common/IGenericaVO.h"

class ICargable
{
public:
	//ICargable(); // se comenta pues para las clases con constructor privado genera conflicto
	/**
	 * @param objetoXML contiene los datos a ser leidos
	 * este metodo carga en el objeto que implemente ICargable, los datos datos que recibe desde objetoXML
	 */
	virtual int readFrom(IGenericaVO * objetoXML) = 0;
};

#endif //_ICARGABLE_H_
