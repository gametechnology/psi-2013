#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent(Entity* parent):Component(parent)
{
	entityParent = parent;
	thrust = 0;
}

BasicMoverComponent::~BasicMoverComponent()
{
	
}

void BasicMoverComponent::update()
{
	vector3df direction = entityParent->orientation.rotationToDirection(vector3df(1,0,0));
	entityParent->velocity.set(direction * thrust);
	//printf("position: %f, %f, %f\n", entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	//printf("forwardMovement: %f, %f, %f\n", direction.X * thrust, direction.Y * thrust, direction.Z * thrust);
}

void BasicMoverComponent::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == PacketType::CLIENT_SHIP_MOVEMENT)
    {
		//Vec3 position, Vec3 orientation, Vec3 acceleration, Vec3 angularAcceleration
        vector3df position;
		vector3df orientation;
		vector3df acceleration;
		vector3df angularAcceleration;

		//Read the information from the network packet
		packet >> position;
		packet >> orientation;
		packet >> acceleration;
		packet >> angularAcceleration;

		//Apply updates
		entityParent->position = position;
		entityParent->orientation = orientation;
		entityParent->accelaration = acceleration;
		entityParent->angularAccelaration = angularAcceleration;
    }
}