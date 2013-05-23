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
}

BasicShipMover::~BasicShipMover() { 

}


void BasicShipMover::update() {

	//FORWARD/BACKWARD
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_W))
		move(_ship, core::vector3df(0, 0, 2.0));
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_S))
		move(_ship, core::vector3df(0, 0, -2.0));

	//PITCH
	if (getGame()->input->isKeyboardButtonDown(KEY_UP))
		pitch(_ship, 1.0);
	if (getGame()->input->isKeyboardButtonDown(KEY_DOWN))
		pitch(_ship, -1.0);

	//TURN 
	if (getGame()->input->isKeyboardButtonDown(KEY_LEFT))
		turn(_ship, -1.0);
	if (getGame()->input->isKeyboardButtonDown(KEY_RIGHT))
		turn(_ship, 1.0);

	//ROLL
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_A))
		roll(_ship, 1.0);
	if (getGame()->input->isKeyboardButtonDown(KEY_KEY_D))
		roll(_ship, -1.0);

	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	//movementPacket << id; // ID van het ship
	movementPacket << entity->transform->position;
	movementPacket << entity->transform->rotation;
	movementPacket << entity->transform->velocity; 
	movementPacket << entity->transform->acceleration; 
	movementPacket << entity->transform->angularAccelaration; 
	movementPacket << entity->transform->angularVelocity;

	//Send packet to server
	if(Network::GetInstance()->IsServer())
		Network::GetInstance()->SendServerPacket(movementPacket, false);
}