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

	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	NetworkPacket movementPacket = NetworkPacket(PacketType::CLIENT_SHIP_MOVEMENT);
	movementPacket << vector3df(entityParent->position);
	movementPacket << vector3df(entityParent->orientation);
	movementPacket << vector3df(entityParent->velocity);
	movementPacket << vector3df(entityParent->accelaration);
	movementPacket << vector3df(entityParent->angularAccelaration);
	movementPacket << vector3df(entityParent->angularVelocity);

	//Send packet to server
	if(Network::GetInstance()->IsServer())
		Network::GetInstance()->SendServerPacket(movementPacket, false);
}

