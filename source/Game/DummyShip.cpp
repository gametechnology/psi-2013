#include "DummyShip.h"


DummyShip::DummyShip(vector3df position) : Enemy ()
{
	this->transform->position = &position;
}

DummyShip::~DummyShip(void)
{
	
}

void DummyShip::onAdd() {
	health = 100;
	this->env = game->device->getGUIEnvironment();
	irr::core::stringw strShipHealth = "ship health: "; 
	this->shipHealth = env->addStaticText(strShipHealth.c_str(), rect<s32>(40,80,300,100), false);
	this->shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));
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
	health = 100;
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
	if (health < 0)
	{
		health = 0;
	}
	if (health == 0)
	{
		std::cout<<"DummyShip is destroyed!!!";
	}
	stringw strShipHealth = "ship health: "	+ this->health;
	this->shipHealth->setText((varToString("Ship HP : ",(float)this->health)).c_str());
	Entity :: update();
}

//Swith to a specific station

void DummyShip :: draw()
{
	Entity :: draw();
}

void DummyShip :: contactResolverA(Entity* input)
{
	std::printf("HIT on Ship!");
	Entity::contactResolverA(input);
}
