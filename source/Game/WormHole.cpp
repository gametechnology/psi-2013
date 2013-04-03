#include "WormHole.h"

WormHole::WormHole(Composite* parent, unsigned int id, irr::core::vector3df position) : Entity(parent) {
	createNode("../assets/sydney.md2");
	this->id = id;
	this->position = position;
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
	Entity::~Entity();
}
