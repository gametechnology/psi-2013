#include "Engine\Entity.h"
#include "Engine\Game.h"
#include "Engine\Transform.h"

Entity::Entity() : Composite() {
	
}

void Entity::update() {
	
}

void Entity::onAdd() {
	addComponent(new Transform());

	if (parent != NULL && parent->initialized)
		handleMessage(1); // Calling init if adding something while the game already has been initialized
}

void Entity::addComponent(Component* component) {
	components.push_back(component);
	component->entity = this;

	component->onAdd();
}

void Entity::addChild(Entity* child) {
	children.push_back(child);
	child->parent = this;

	child->onAdd();
}