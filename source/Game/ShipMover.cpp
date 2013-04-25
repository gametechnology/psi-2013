#include "ShipMover.h"
#include "NetworkInterface.h"

using namespace irr;
using namespace core;

ShipMover::ShipMover(Ship* parent):BasicMoverComponent(parent)
{
	maxFwdSpeed = 10;
	maxBwdSpeed = -10;

	//The ship listens to certain packet types
	Network::GetInstance()->AddListener(PacketType::CLIENT_SHIP_MOVEMENT, this);
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
	//Roll 
	if (Game::input->isKeyboardButtonDown(KEY_KEY_Q))
		entityParent->orientation.X -= 1.01f;   
	if (Game::input->isKeyboardButtonDown(KEY_KEY_E))
		entityParent->orientation.X += 1.01f;   
	
	//YAW 
	if (Game::input->isKeyboardButtonDown(KEY_KEY_A))
		entityParent->orientation.Y -= 1.01f;   
	if (Game::input->isKeyboardButtonDown(KEY_KEY_D))
		entityParent->orientation.Y += 1.01f;   

	//PITCH
	if (Game::input->isKeyboardButtonDown(KEY_KEY_W))
		entityParent->orientation.Z -= 1.01f;   
	if (Game::input->isKeyboardButtonDown(KEY_KEY_S))
		entityParent->orientation.Z += 1.01f;   
	
	
	BasicMoverComponent::update();

	//Vec3 position, Vec3 orientation, Vec3 acceleration, Vec3 angularAcceleration
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	movementPacket << vector3df(entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	movementPacket << vector3df(entityParent->orientation.X, entityParent->orientation.Y, entityParent->orientation.Z);
	movementPacket << vector3df(entityParent->accelaration.X, entityParent->accelaration.Y, entityParent->accelaration.Z);
	movementPacket << vector3df(entityParent->angularAccelaration.X, entityParent->angularAccelaration.Y, entityParent->angularAccelaration.Z);

	//Send packet to server
	Network::GetInstance()->SendServerPacket(movementPacket, false);
}

