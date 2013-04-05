#include "ShipMover.h"
#include "Engine\Entity.h"
#include "Ship.h"


ShipMover::ShipMover(Composite* parent, Thruster* thrusters[]) : Component(parent)
{
	ShipMover::thrusters = thrusters;

	

}


ShipMover::~ShipMover(void)
{


}

void ShipMover::update(){
	//input logic
	ShipMover::linearAcceleration = vector3df(0,0,0);
	ShipMover::angularAcceleration = vector3df(0,0,0);
	for(int i = 0; i < sizeof(thrusters); i++){
		ShipMover::linearAcceleration+= thrusters[i]->linearForce;
		ShipMover::angularAcceleration += thrusters[i]->angularForce;
	}
	((Ship*)parent)->accelaration = linearAcceleration;
	((Ship*)parent)->angularAccelaration = angularAcceleration;

}

void ShipMover::init(){

}

void ShipMover::draw(){


}
