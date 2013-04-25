#include "ShipMover.h"
#include "NetworkInterface.h"

using namespace irr;
using namespace core;

ShipMover::ShipMover(Ship* parent) : BasicMoverComponent() {
	maxFwdSpeed = 10;
	maxBwdSpeed = -10;
}

ShipMover::~ShipMover() {

}

void ShipMover::update() {
	if (Game::input->isKeyboardButtonDown(KEY_KEY_R) && thrust < maxFwdSpeed)
		thrust += 0.01f;
	if (Game::input->isKeyboardButtonDown(KEY_KEY_F) && thrust > maxBwdSpeed)
		thrust -= 0.01f;

	//Roll 
	if (Game::input->isKeyboardButtonDown(KEY_KEY_Q))
		entity->transform->angularVelocity->X -= 1;
	if (Game::input->isKeyboardButtonDown(KEY_KEY_E))
		entity->transform->angularVelocity->X += 1;
	
	//YAW 
	if (Game::input->isKeyboardButtonDown(KEY_KEY_A))
		entity->transform->angularVelocity->Y -= 1;
	if (Game::input->isKeyboardButtonDown(KEY_KEY_D))
		entity->transform->angularVelocity->Y += 1;   

	//PITCH
	if (Game::input->isKeyboardButtonDown(KEY_KEY_W))
		entity->transform->angularVelocity->Z -= 1;   
	if (Game::input->isKeyboardButtonDown(KEY_KEY_S))
		entity->transform->angularVelocity->Z += 1;

	//printf("rotation: x:%f, y:%f, z:%f\n", entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);

	*entity->transform->angularVelocity *= 0.90f;
	
	
	BasicMoverComponent::update();

	//Vec3 position, Vec3 orientation, Vec3 acceleration, Vec3 angularAcceleration
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	vector3df yey = vector3df(entity->transform->position->X, entity->transform->position->Y, entity->transform->position->Z);
	movementPacket << yey;
	//movementPacket << vector3df(entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);
	//movementPacket << vector3df(entityParent->accelaration.X, entityParent->accelaration.Y, entityParent->accelaration.Z);
	//movementPacket << vector3df(entityParent->angularAccelaration.X, entityParent->angularAccelaration.Y, entityParent->angularAccelaration.Z);

	//Send packet to server
	Network::GetInstance()->SendPacket(movementPacket, false);
}