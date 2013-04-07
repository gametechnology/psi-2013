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
	
	if(eventReceiver.IsKeyDown(KEY_KEY_W)){
		thrusters[0]->print();
		ShipMover::linearAcceleration += thrusters[0]->linearForce;
		ShipMover::angularAcceleration += (thrusters[0]->angularAccelaration * 0.0001);
	}
	if(eventReceiver.IsKeyDown(KEY_KEY_A)){
		thrusters[1]->print();
		ShipMover::linearAcceleration += thrusters[1]->linearForce;
		ShipMover::angularAcceleration += (thrusters[1]->angularAccelaration * 0.0001);
	}
	if(eventReceiver.IsKeyDown(KEY_KEY_D)){
		thrusters[2]->print();
		ShipMover::linearAcceleration += thrusters[2]->linearForce;
		ShipMover::angularAcceleration += (thrusters[2]->angularAccelaration * 0.0001);
	}
	
	((Ship*)parent)->accelaration = linearAcceleration;
	((Ship*)parent)->angularAccelaration = angularAcceleration;
	
}

void ShipMover::init(){

}

void ShipMover::draw(){


}
