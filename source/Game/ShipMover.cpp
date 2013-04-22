#include "ShipMover.h"
#include "NetworkInterface.h"

using namespace irr;
using namespace core;

ShipMover::ShipMover(Ship* parent):BasicMoverComponent(parent)
{
	maxFwdSpeed = 10;
	maxBwdSpeed = -10;
}

ShipMover::~ShipMover()
{
}

void ShipMover::update()
{
	if (Game::input->isKeyboardButtonDown(KEY_KEY_R) && thrust < maxFwdSpeed)
		thrust += 0.01f;
	if (Game::input->isKeyboardButtonDown(KEY_KEY_F) && thrust > maxBwdSpeed)
		thrust -= 0.01f;

	BasicMoverComponent::update();

	//Vec3 position, Vec3 orientation, Vec3 acceleration, Vec3 angularAcceleration
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	vector3df yey = vector3df(entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	movementPacket << yey;
	//movementPacket << vector3df(entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);
	//movementPacket << vector3df(entityParent->accelaration.X, entityParent->accelaration.Y, entityParent->accelaration.Z);
	//movementPacket << vector3df(entityParent->angularAccelaration.X, entityParent->angularAccelaration.Y, entityParent->angularAccelaration.Z);

	//Send packet to server
	Network::GetInstance()->SendPacket(movementPacket, false);
}