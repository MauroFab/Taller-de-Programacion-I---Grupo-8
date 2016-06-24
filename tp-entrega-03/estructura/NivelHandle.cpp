#include "NivelHandle.h"

NivelHandle::NivelHandle()
{
	total_levels =9;
	current_level = 0;	
}

NivelHandle::~NivelHandle()
{
}
void NivelHandle::play_next()
{
    current_level++;
    JuegoXml * loadD = JuegoXml::getInstance();
    loadD->load();
    loadD->set_levels(current_level);
    start_current_level();
    return;
}
void NivelHandle::start_current_level()
{
    JuegoXml * loadD = JuegoXml::getInstance();
	if (current_level > total_levels) {
/*
		GuiGame.bonus_amount = 0;
		GuiGame.ring_amount_aux = 0;
*/	
		loadD->set_levels(1);
		loadD->load();
		loadD->load();
		current_level = 1;
	}
	if (current_level == 0) {
		loadD->load();

	}
	Escenario * nivelActual = loadD->nivel_actual;
	JuegoContainer * con = JuegoContainer::getInstance();
	con->set_state(nivelActual);
    return;
}
void NivelHandle::load_level_data()
{
    current_level = 1;
    JuegoXml * loadD = JuegoXml::getInstance();
    loadD->load();
    current_level = loadD->get_levels();
    return;
}