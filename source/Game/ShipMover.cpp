#include "ShipMover.h"
#include "Engine\Entity.h"


ShipMover::ShipMover(Composite* parent, Thruster* thrusters[]) : Component(parent)
{
	ShipMover::thrusters = thrusters;
}


ShipMover::~ShipMover(void)
{


}

void ShipMover::update(){

}

void ShipMover::init(){

}

void ShipMover::draw(){


}
