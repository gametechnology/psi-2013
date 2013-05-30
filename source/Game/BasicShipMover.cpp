/* 
* Basic ship mover, does not use thrusters.
*
* Use keys W and S to got forward or backward.
* Use keys Arrow Up and Arrow Down to pitch.
* Use keys Arrow Left and Arrow Right to turn.
* Use keys A and D to roll.
*/
#include "BasicShipMover.h"

using namespace irr;
using namespace irr::core;

BasicShipMover::BasicShipMover(Core* core, Ship *ship) : BasicMoverComponent(ship) 
{
	_core = core;
}

BasicShipMover::~BasicShipMover() { 

}


void BasicShipMover::update()
{
	powerEnable = dynamic_cast<Ship*>(_parent)->GetStation(ST_HELM)->HasPower();
	powerEnable = true; //workAround to be commented when the switch between stations is working 
	if(powerEnable){ //power to steer
		//FORWARD/BACKWARD
		if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_W))
			move(vector3df(0, 0, 2.0));
		if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_S))
			move(vector3df(0, 0, -2.0));

		//PITCH
		if (_core->getInput()->isKeyboardButtonDown(KEY_UP))
			pitch(1.0);
		if (_core->getInput()->isKeyboardButtonDown(KEY_DOWN))
			pitch(-1.0);

		//TURN 
		if (_core->getInput()->isKeyboardButtonDown(KEY_LEFT))
			turn(-1.0);
		if (_core->getInput()->isKeyboardButtonDown(KEY_RIGHT))
			turn(1.0);

		//ROLL
		if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_A))
			roll(1.0);
		if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_D))
			roll(-1.0);

	}//endif of the power to steer

	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	/*NetworkPacket movementPacket = NetworkPacket(CLIENT_SHIP_MOVEMENT);
	//movementPacket << id; // ID van het ship
	movementPacket << *_parent->getPosition();
	movementPacket << *_parent->getRotation();
	movementPacket << *_parent->getVelocity(); 
	movementPacket << *_parent->getAcceleration(); 
	movementPacket << *_parent->getAngularAcceleration(); 
	movementPacket << *_parent->getAngularVelocity();*/

	//Send packet to server
	//if(Network::GetInstance()->IsServer())
	//Network::GetInstance()->SendPacketToAllClients(movementPacket, false);

	BasicMoverComponent::update();
}