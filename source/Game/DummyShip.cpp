#include "DummyShip.h"
#include "Enemy.h"


DummyShip::DummyShip(vector3df position) : Enemy ()
{
	this->transform->position = &position;
}

DummyShip::~DummyShip(void)
{
	
}

void DummyShip::onAdd() {
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);
	Entity::onAdd();
}

void DummyShip::init() 
{
	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	this->transform->position = &startPosition;
	this->transform->rotation = &startRotation;

	Entity::init();
}


irr::core::stringw DummyShip::varToString(irr::core::stringw str1, float var){
	stringw str = L"";
	str += str1;
	str += (int)var;	
	return str;
}
irr::core::stringw DummyShip::varToString(irr::core::stringw str1, float var, irr::core::stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}

void DummyShip :: update()
{
	Entity :: update();
}

//Swith to a specific station

void DummyShip :: draw()
{
	Entity :: draw();
}
