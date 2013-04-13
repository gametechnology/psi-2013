#include "Engine\Entity.h"
#include "Engine\Game.h"
#include "Engine\Transform.h"

Entity::Entity() : Composite() {
	
}

void Entity::update() {
	
}

void Entity::onAdd() {
	addComponent(new Transform());
}

void Entity::addComponent(Component* component) {
	components.push_back(component);
	component->entity = this;

	component->handleMessage(0); // Awake
	component->handleMessage(1); // I
}

void Entity::addChild(Entity* child) {
	children.push_back(child);
	child->parent = this;

	child->handleMessage(0);
}