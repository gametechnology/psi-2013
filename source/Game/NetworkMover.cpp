#include "NetworkMover.h"

NetworkMover::NetworkMover() : Component()
{
	
}

void NetworkMover::onAdd() {
	Component::onAdd();
}

void NetworkMover::init() {
	Component::init();
}

NetworkMover::~NetworkMover() {
	Component::~Component();
}

void NetworkMover::update() {
	Component::update();
}

void NetworkMover::HandleNetworkMessage(NetworkPacket packet) {
	if (packet.GetType() == PacketType::OTHER_SHIP_POSITION) {
		irr::core::vector3df position;
		packet >> position;

		entity->transform->position = &position;
    }
}