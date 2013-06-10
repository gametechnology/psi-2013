/* 
* Basic ship mover, does not use thrusters.
*
* Use keys W and S to got forward or backward.
* Use keys Arrow Up and Arrow Down to pitch.
* Use keys Arrow Left and Arrow Right to turn.
* Use keys A and D to roll.
*/
#include "BasicShipMover.h"

BasicShipMover::BasicShipMover(Ship *ship) : BasicMoverComponent() {
	this->_ship = ship;
	this->maxSpeed = 0;
	invertVerticalAxis = false;
}

BasicShipMover::~BasicShipMover() { 

}


void BasicShipMover::update() {
	powerEnable = _ship->GetStation(ST_HELM)->HasPower();
	powerEnable = true; //workAround to be commented when the switch between stations is working

	if (getGame()->input->isKeyboardButtonReleased(KEY_KEY_Y))
		invertVerticalAxis = !invertVerticalAxis;

	if(powerEnable){ //power to steer
	//FORWARD/BACKWARD
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_W))
		move(_ship, core::vector3df(0, 0, maxSpeed));
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_S))
		move(_ship, core::vector3df(0, 0, -maxSpeed));

	//PITCH
	float temp = maxSpeed;
	if (invertVerticalAxis) {
		temp = -maxSpeed;
	}
	if (getGame()->input->isKeyboardButtonDown(KEY_UP))
		//pitch(_ship, maxSpeed);
		pitch(_ship, core::vector3df(temp, 0, 0));
	if (getGame()->input->isKeyboardButtonDown(KEY_DOWN))
		//pitch(_ship, -maxSpeed);
		pitch(_ship, core::vector3df(-temp, 0, 0));

	//TURN 
	if (getGame()->input->isKeyboardButtonDown(KEY_LEFT))
		//turn(_ship, -maxSpeed);
		turn(_ship, core::vector3df(0, -maxSpeed, 0));
	if (getGame()->input->isKeyboardButtonDown(KEY_RIGHT))
		//turn(_ship, maxSpeed);
		turn(_ship, core::vector3df(0, maxSpeed, 0));

	//ROLL
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_A))
		roll(_ship, maxSpeed);
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_D))
		roll(_ship, -maxSpeed);

	}//endif of the power to steer

	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	//movementPacket << id; // ID van het ship
	movementPacket << *_ship->transform->position;
	movementPacket << *_ship->transform->rotation;
	movementPacket << *_ship->transform->velocity; 
	movementPacket << *_ship->transform->acceleration; 
	movementPacket << *_ship->transform->angularAccelaration; 
	movementPacket << *_ship->transform->angularVelocity;

	//Send packet to server
	//if(Network::GetInstance()->IsServer())
		Network::GetInstance()->SendPacketToAllClients(movementPacket, false);
}

void BasicShipMover::setMaxSpeed(float speed)
{
	maxSpeed = speed;
}