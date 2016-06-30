#include "GrupoItems.h"

GrupoItems::GrupoItems():ObjetoItem()
{
	solid = false;
	_group = true;
	this->_first = true;
	_last.x = 0;
	_last.y = 0;
}

GrupoItems::~GrupoItems()
{
}

ObjetoItem* GrupoItems::add(ObjetoItem * arg1) {
	return add(arg1, true);
}

ObjetoItem* GrupoItems::add(ObjetoItem * arg1, bool arg2) {
	this->members.push_back(arg1);
//	if (arg2) {
//		arg1.scrollFactor = scrollFactor;
//	}
	return arg1;
}

void GrupoItems::saveOldPosition()
{
    if (this->_first)
    {
        this->_first = false;
        this->_last.x = 0;
        this->_last.y = 0;
        return;
    }
    this->_last.x = x;
    this->_last.y = y;
    return;
}
void GrupoItems::updateMembers()
{
	int pos_x=0;
	int pos_y=0;
	ObjetoItem * elem=NULL;
	bool bCambio=false;
	if (!(x == this->_last.x) || !(y == this->_last.y))
	{
		bCambio = true;
		pos_x = x - this->_last.x;
		pos_y = y - this->_last.y;
	}
	int cantidad=this->members.size();
	int posElem=0;
	while (posElem < cantidad)
	{
		elem = (ObjetoItem *)this->members[posElem];

		if (!((elem) == NULL) && elem->existe)
		{
			if (bCambio)
			{
				if (elem->_group)
				{
					elem->reset(elem->x + pos_x, elem->y + pos_y);
				}
				else
				{
					elem->x = elem->x + pos_x;
					elem->y = elem->y + pos_y;
				}
			}
			if (elem->activo)
			{
				elem->update();
			}
			if (bCambio && elem->get_solid())
			{
				elem->colHullX.width = elem->colHullX.width + (pos_x > 0 ? pos_x : -pos_x);
				if (pos_x < 0)
				{
					elem->colHullX.x = elem->colHullX.x + pos_x;
				}
				elem->colHullY.x = x;
				elem->colHullY.height = elem->colHullY.height + (pos_y > 0 ? pos_y : -pos_y);
				if (pos_y < 0)
				{
					elem->colHullY.y = elem->colHullY.y + pos_y;
				}
				elem->colVector.x = elem->colVector.x + pos_x;
				elem->colVector.y = elem->colVector.y + pos_y;
			}
		}
		posElem = (posElem + 1);
	}
	return;
}

void GrupoItems::update()
{
	this->saveOldPosition();
	updateMotion();
	this->updateMembers();
//            updateFlickering();
    return;
}
void GrupoItems::renderMembers()
{
	ObjetoItem * elem=NULL;
    int cantidad=this->members.size();
    int posElem=0;
    while (posElem < cantidad)
    {
        elem = (ObjetoItem *)this->members[posElem];
        if (!(elem == NULL) && elem->existe && elem->visible)
        {
            elem->render();
        }
        posElem = (posElem + 1);
    }
    return;
}
void GrupoItems::render()
{
    this->renderMembers();
    return;
}
void GrupoItems::killMembers()
{
    ObjetoItem * elem=NULL;
    int cantidad=this->members.size();
    int posElem=0;
    while (posElem < cantidad)
    {
        elem = (ObjetoItem *)this->members[posElem];
        if (elem != NULL)
        {
            elem->kill();
        }
        posElem = (posElem + 1);
    }
    return;
}
void GrupoItems::kill()
{
    this->killMembers();
    ObjetoItem::kill();
    return;
}
void GrupoItems::destroyMembers() {
	ObjetoItem * elem = NULL;
	int cantidad = this->members.size();
	int posElem = 0;
	while (posElem < cantidad) {
		elem = (ObjetoItem *) this->members[posElem];
		if (elem != NULL) {
			elem->destroy();
		}
		posElem = (posElem + 1);
	}
	this->members.clear();// = 0;
	return;
}

void GrupoItems::destroy() {
	this->destroyMembers();
	ObjetoItem::destroy();
	return;
}
