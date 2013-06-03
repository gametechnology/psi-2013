#include "DummyShip.h"


DummyShip::DummyShip(vector3df position) : Enemy ()
{
	this->transform->position = &position;
}

DummyShip::~DummyShip(void)
{
	
}

void DummyShip::onAdd() {
	//Creates the visual feedback of health. The ship, the GUIenviroment to display the feed back, adds the collision component and handles everything to at it to the scene
	this->setHealth(100);
	//the the GUIEnvironment of the Game
	this->env = game->device->getGUIEnvironment();

	//Create a string with the health of the dummyship
	irr::core::stringw strShipHealth = "ship health: "; 
	this->shipHealth = env->addStaticText(strShipHealth.c_str(), rect<s32>(40,80,300,100), false);
	this->shipHealth->setOverrideColor(video::SColor(255, 255, 255, 255));

	//Add the model
	IrrlichtNode *model = new IrrlichtNode( irr::io::path("../assets/Models/myship.obj"));
	addChild(model);
	Entity::onAdd();

	//Make it collision
	Collision* collision = new Collision();
	addComponent(collision);
}

void DummyShip::init() 
{
	//Place the DummyShip in the Scene
	startPosition = vector3df(0,0,-100);
	startRotation = vector3df(0,0,0);
	this->transform->position = &startPosition;
	this->transform->rotation = &startRotation;
	this->setHealth(100);
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
	//checks for health below zero, if so it's reset to 0 and the check will say the dummy ship is destroyed and updates the text on screen to the current hp
	if (getHealth() < 0)
	{
		setHealth(0);
	}
	if (getHealth() == 0)
	{
		std::cout<<"DummyShip is destroyed!!!";
	}
	stringw strShipHealth = "ship health: "	+ this->getHealth();
	this->shipHealth->setText((varToString("Ship HP : ",(float)this->getHealth())).c_str());
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
