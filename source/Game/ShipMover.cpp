#include "ShipMover.h"
#include "Engine\Entity.h"
#include "Ship.h"


ShipMover::ShipMover(Ship* ship) : Component(ship)
{
	this->_ship = ship;
}

ShipMover::~ShipMover(void)
{


}

void ShipMover::update(){
	//input logic
	
	ShipMover::linearAcceleration = vector3df(0,0,0);
	ShipMover::angularAcceleration = vector3df(0,0,0);

	if(Game::input->isKeyboardButtonPressed(KEY_KEY_W))
	{
		this->linearAcceleration += _ship->GetThrusters()[0]->linearForce;
		this->angularAcceleration += (_ship->GetThrusters()[0]->angularAccelaration * 0.0001);
	}
	if(Game::input->isKeyboardButtonPressed(KEY_KEY_A))
	{
		this->linearAcceleration += _ship->GetThrusters()[1]->linearForce;
		this->angularAcceleration += (_ship->GetThrusters()[1]->angularAccelaration * 0.0001);
	}
	if(Game::input->isKeyboardButtonPressed(KEY_KEY_D))
	{
		this->linearAcceleration += _ship->GetThrusters()[2]->linearForce;
		this->angularAcceleration += (_ship->GetThrusters()[2]->angularAccelaration * 0.0001);
	}
	
	_ship->accelaration = linearAcceleration;
	_ship->angularAccelaration = angularAcceleration;	
}

void ShipMover::init(){

}

void ShipMover::draw(){


}
