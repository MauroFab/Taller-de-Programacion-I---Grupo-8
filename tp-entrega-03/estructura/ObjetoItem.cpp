#include "ObjetoItem.h"

ObjetoItem::ObjetoItem()
{
	this->x = 0;
	this->y = 0;
	existe = true;
	activo = true;
	visible = true;
	_solid = true;
	this->moves = true;
	this->bMuerto = false;
	_group = false;
	_pZero.x = 0;
	_pZero.y = 0;
	_point.x = 0;
	_point.y = 0;
	velocity.x = 0;
	velocity.y = 5;	
}

ObjetoItem::~ObjetoItem()
{
}
void ObjetoItem::setVisible(bool visible){
	this->visible = visible;
}
bool ObjetoItem::getVisible(){
	return 	this->visible;
}

void ObjetoItem::destroy() {
	return;
}
bool ObjetoItem::get_solid()
{
    return this->_solid;
}

void ObjetoItem::refreshHulls() {
	this->colHullX.x = x;
	this->colHullX.y = y;
	this->colHullX.width = 32;//width;
	this->colHullX.height = 32;//height;
	this->colHullY.x = x;
	this->colHullY.y = y;
	this->colHullY.width = 32;//width;
	this->colHullY.height = 32;//height;
	return;
}

void ObjetoItem::updateMotion(){
	UtilJuego * util = UtilJuego::getInstance();
	double deltaVelAng;
	FPoint elemPoint_2;
	FPoint elemPoint_5;
	double p_elapsed = 0.1333333;
//	System.out.println("updateMotion =" + p_elapsed);
	int pos_y;
	if (!this->moves) {
		return;
	}
	if (this->_solid) {
		this->refreshHulls();
	}
//	this->onFloor = false;
/*
	deltaVelAng = (FlxU.computeVelocity(this->angularVelocity, this->angularAcceleration, this->angularDrag, this->maxAngular) - this->angularVelocity) / 2;
	this->angularVelocity = this->angularVelocity + deltaVelAng;
	this->angle = this->angle + this->angularVelocity * p_elapsed;
	if (this->thrust == 0) {
		elemPoint_2 = _pZero;
	} else {
		elemPoint_2 = FlxU.rotatePoint(-this->thrust, 0, 0, 0, this->angle);
		if ((pos_y = (elemPoint_5 = FlxU.rotatePoint(-this->maxThrust, 0, 0, 0, this->angle)).x > 0 ? elemPoint_5.x : -elemPoint_5.x) > (elemPoint_5.y > 0 ? elemPoint_5.y : -elemPoint_5.y)) {
			elemPoint_5.y = pos_y;
		} else {
			pos_y = elemPoint_5.y > 0 ? elemPoint_5.y : -elemPoint_5.y;
		}
		int loc7;
		this->maxVelocity.y = loc7 = pos_y > 0 ? pos_y : -pos_y;
		this->maxVelocity.x = loc7;
	}
	*/
	deltaVelAng = 0;//(FlxU.computeVelocity(this->velocity.x, this->acceleration.x + elemPoint_2.x, this->drag.x, this->maxVelocity.x) - this->velocity.x) / 2;
	this->velocity.x = (int) (this->velocity.x + deltaVelAng);
	int deltaX = (int) (this->velocity.x * p_elapsed);
	//-coreccion en caso de deltas en = 0;
	//--------------------------------
	if (deltaX == 0 && this->velocity.x > 0) {
		deltaX = util->techo(this->velocity.x + deltaVelAng);
	}

	deltaVelAng = 0;//(FlxU.computeVelocity(this->velocity.y, this->acceleration.y + elemPoint_2.y, this->drag.y, this->maxVelocity.y) - this->velocity.y) / 2;
	this->velocity.x = (int) (this->velocity.y + deltaVelAng);
	int deltaY = (int) (this->velocity.y * p_elapsed);
	//-coreccion en caso de deltas en = 0;
	//--------------------------------
	if (deltaY == 0 && this->velocity.y > 0) {
		deltaY = util->techo(this->velocity.y + deltaVelAng);
	}
	x = x + deltaX;
	y = y + deltaY;
	if (!this->_solid) {
		return;
	}
	this->colVector.x = deltaX;
	this->colVector.y = deltaY;
	this->colHullX.width = this->colHullX.width + (this->colVector.x > 0 ? this->colVector.x : -this->colVector.x);
	if (this->colVector.x < 0) {
		this->colHullX.x = this->colHullX.x + this->colVector.x;
	}
	this->colHullY.x = x;
	this->colHullY.height = this->colHullY.height + (this->colVector.y > 0 ? this->colVector.y : -this->colVector.y);
	if (this->colVector.y < 0) {
		this->colHullY.y = this->colHullY.y + this->colVector.y;
	}
	return;	
}
void ObjetoItem::update()
{
	this->updateMotion();
    return;
}
void ObjetoItem::render()
{
    return;
}
bool ObjetoItem::overlaps(ObjetoItem arg1) {
	return false;
}

void ObjetoItem::kill()
{
    this->existe = false;
    this->bMuerto = true;
    return;
}

void ObjetoItem::getScreenXY(FPoint * arg1) {
	UtilJuego * util = UtilJuego::getInstance();
	
//	if (arg1 == NULL) {
//		arg1 = new FPoint();
//	}
	arg1->x = -1;//(int) (util->piso(x + FlxU.roundingError) + FlxU.floor(FlxG.scroll.x * 1));
	arg1->y = -1;//(int) (util->piso(y + FlxU.roundingError) + FlxU.floor(FlxG.scroll.y * 1));
//	return arg1;
	return;
}

bool ObjetoItem::onScreen() {
	/*
	JuegoContainer * cons = JuegoContainer::getInstance();
	
	this->getScreenXY(&this->_point);
	if (this->_point.x + this_rect.width < 0 || this->_point.x > cons->width || this->_point.y + this_rect.height < 0 || this->_point.y > cons->height) {
		return false;
	}
	*/
	return true;
}

void ObjetoItem::reset(int arg1,int arg2)
{
    x = arg1;
    y = arg2;
    this->existe = true;
    this->bMuerto = false;
    return;
}
