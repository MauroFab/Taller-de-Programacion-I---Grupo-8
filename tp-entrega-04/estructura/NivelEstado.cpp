#include "NivelEstado.h"

NivelEstado::NivelEstado()
{
	this->defaultGroup = new GrupoItems();
}

NivelEstado::~NivelEstado()
{
	delete this->defaultGroup;
}

void NivelEstado::create()
{
    return;
}

ObjetoItem * NivelEstado::add(ObjetoItem * arg1)
{
    return this->defaultGroup->add(arg1);
}
void NivelEstado::preProcess()
{
}
void NivelEstado::update()
{
    this->defaultGroup->update();
    return;
}
void NivelEstado::render()
{
    this->defaultGroup->render();
    return;
}
void NivelEstado::postProcess()
{
    return;
}
void NivelEstado::destroy()
{
    this->defaultGroup->destroy();
    return;
}