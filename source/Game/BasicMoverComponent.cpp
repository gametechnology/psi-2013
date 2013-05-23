#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent() : Component()
{
	thrust = 0;
	Network::GetInstance()->AddListener(PacketType::CLIENT_SHIP_MOVEMENT, this);
}

BasicMoverComponent::~BasicMoverComponent()
{

}

void BasicMoverComponent::update()
{
	irr::core::vector3df direction = entity->transform->rotation->rotationToDirection();
	entity->transform->velocity->set(direction * thrust);
}


void BasicMoverComponent::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == PacketType::CLIENT_SHIP_MOVEMENT)
	{
		//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
		irr::core::vector3df position;
		irr::core::vector3df orientation;
		irr::core::vector3df velocity;
		irr::core::vector3df acceleration;
		irr::core::vector3df angularAcceleration;
		irr::core::vector3df angularVelocity;

		//Read the information from the network packet
		packet >> position;
		packet >> orientation;
		packet >> velocity;
		packet >> acceleration;
		packet >> angularAcceleration;
		packet >> angularVelocity;

		//Apply updates 
		entity->transform->position = &position;
		entity->transform->rotation = &orientation;
		entity->transform->velocity = &velocity;
		entity->transform->acceleration = &acceleration;
		entity->transform->angularAccelaration = &angularAcceleration;
		entity->transform->angularVelocity = &angularVelocity;
	}
}

void BasicMoverComponent::move(Entity *entity, irr::core::vector3df vel)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(*entity->transform->rotation);
	m.transformVect(vel);
	entity->transform->position->set(*entity->transform->position + vel);
	entity->transform->position;

}

void BasicMoverComponent::rotate(Entity *entity, irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(*entity->transform->rotation);
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	entity->transform->rotation->set(m.getRotationDegrees());
}

void BasicMoverComponent::turn(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(0.0f, rot, 0.0f));
}

void BasicMoverComponent::pitch(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(rot, 0.0f, 0.0f));
}

void BasicMoverComponent::roll(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(0.0f, 0.0f, rot));
}