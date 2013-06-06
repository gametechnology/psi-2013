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
}

BasicShipMover::~BasicShipMover() { 

}


void BasicShipMover::update() {
	powerEnable = _ship->GetStation(ST_HELM)->HasPower();
	powerEnable = true; //workAround to be commented when the switch between stations is working 

	std::cout << maxSpeed << "\n";

	if(powerEnable){ //power to steer
	//FORWARD/BACKWARD
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_W))
		move(_ship, core::vector3df(0, 0, maxSpeed));
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_S))
		move(_ship, core::vector3df(0, 0, -maxSpeed));

	//PITCH
	if (getGame()->input->isKeyboardButtonDown(KEY_UP))
		pitch(_ship, maxSpeed);
	if (getGame()->input->isKeyboardButtonDown(KEY_DOWN))
		pitch(_ship, -maxSpeed);

	//TURN 
	if (getGame()->input->isKeyboardButtonDown(KEY_LEFT))
		turn(_ship, -maxSpeed);
	if (getGame()->input->isKeyboardButtonDown(KEY_RIGHT))
		turn(_ship, maxSpeed);

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