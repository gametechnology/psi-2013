#include "Ship.h"
#include <Windows.h>

Ship::Ship(Composite * parent, vector3df position, vector3df rotation) : Entity(parent)
{
	Ship::drag = 0.99;
	Ship::position = position;
	Ship::orientation = rotation;
}

Ship::Ship(Composite* parent) : Entity(parent){

}


Ship::~Ship(void)
{
}

void Ship::init(){

	Entity::init();
	
	HelmStation* helmStation = new HelmStation(this);
	addComponent(helmStation);

	camera = new Camera(this, vector3df(0,0,0), vector3df(0,0,0));
	this->addComponent(camera);

	//thrusters[0] = new Thruster(this, vector3df(0,0, -4), vector3df(0,0, -4));

}

void Ship::update(){
	Entity::update();
}

void Ship::handleMessage(unsigned int message, void* data){
	
}
