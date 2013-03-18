#include "Planet.h"
#include "Messages.h"

Planet::Planet(Composite* parent) : Entity(parent) {
	createNode("sydney.md2");
}

Planet::~Planet() {
	Entity::~Entity();
}
