#include <Engine\Entity.h>
#include "Engine\Component.h"
#include "Engine\Transform.h"
#include "Engine\Scene.h"

Entity::Entity() : Composite() {
	transform = new Transform();
	addComponent(transform);
}

Entity::~Entity() {

}

void Entity::onAdd() {
	Composite::onAdd();

	// If this is true, it means the object is added during runtime, and will miss the base initialize.
	// Therefore initialize it after it has been added.
	if (parent != NULL && parent->initialized) {
		init();
	}
}

void Entity::init() {
	Composite::init();

	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->init();
	}

	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->init();
	}
}

void Entity::handleMessage(unsigned int message) {
	Composite::handleMessage(message);

	if (enabled) {
		for (unsigned int i = 0; i < components.size(); i++) {
			components[i]->handleMessage(message);
		}

		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->handleMessage(message);
		}
	}
}

void Entity::update() {
	Composite::update();

	if (!enabled) return;
		
	for (unsigned int i = 0; i < components.size(); i++) {
		if (components[i] == NULL) {
			components.erase(components.begin()+i--);
		} else if (components[i]->destroyed) {
			Component* component = components[i];
			components.erase(components.begin()+i--);
			delete component;
		} else {
			if ( components[i]->enabled == false ) continue;
			components[i]->update();
		}
	}
	
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i] == NULL) {
			children.erase(children.begin()+i--);
		} else if (children[i]->destroyed) {
			Entity* child = children[i];
			children.erase(children.begin()+i--);
			delete child;
		} else {
			if ( children[i]->enabled == false ) continue;
			children[i]->update();
		}
	}
}

void Entity::lateUpdate() {
	Composite::lateUpdate();

	if (enabled) {
		for (unsigned int i = 0; i < components.size(); i++) {
			components[i]->lateUpdate();
		}

		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->lateUpdate();
		}
	}
}

void Entity::draw() {
	Composite::draw();

	if (enabled) {
		for (unsigned int i = 0; i < components.size(); i++) {
			components[i]->draw();
		}

		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->draw();
		}
	}
}

void Entity::addComponent(Component* component) {
	components.push_back(component);
	component->entity = this;

	component->onAdd();
}

bool Entity::removeComponent(Component* component) {
	for (unsigned int i = 0; i < components.size(); i++) {
		if (components[i] == component) {
			Component* component = components[i];
			components[i] = NULL;

			components.erase(components.begin()+i);
			component->destroy();
			delete component;
			return true;
		}
	}

	return false;
}

void Entity::addChild(Entity* child) {
	children.push_back(child);
	child->parent = this;
	child->game = game;
 
	if (dynamic_cast<Scene*>(this) != NULL)
		child->scene = dynamic_cast<Scene*>(this);
	else if (child->scene != NULL)
		child->scene = scene;

	child->onAdd();
}

bool Entity::removeChild(Entity* child) {
	return removeChild(child, true) != NULL;
}

bool Entity::removeChild(Entity* child, bool deleteChild) {
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i] == child) {
			Entity* child = children[i];
			children[i] = NULL;

			if (deleteChild) {

				if(children.size()>0) {
					// Deleting the Entitys of this Child
					int childIndex = child->children.size()-1;
					while(childIndex > 0){
						child->removeChild( child->children[childIndex],true );
						childIndex = child->children.size()-1;
					}

					// Deleting the Components of this Child
					int componentIndex = child->components.size()-1;
					while(componentIndex > 0){
						child->removeComponent( child->components[componentIndex] );
						componentIndex = child->components.size()-1;
					}
				}

				children.erase(children.begin()+i);
				child->destroy();
				delete child;
				return true; // I know child doesn't exist here anymore, but the pointer will contain 0xcdcdcdcd instead of NULL so we know if something is deleted
			} else
				return true;
		}
	}

	return false;
}

void Entity::contactResolverA(Entity* _input)
{
	float deltamass = (this->transform->radii->X / _input->transform->radii->X);
	irr::core::vector3df deltavelocity = *this->transform->velocity - *_input->transform->velocity;
	irr::core::vector3df componentThisToBal = Collision::componentOnto(*_input->transform->position - *this->transform->position, deltavelocity);
    irr::core::vector3df componentNormalToBal = deltavelocity - componentThisToBal;
    irr::core::vector3df thisMassComponent = componentThisToBal * (((deltamass- 1) / (deltamass + 1)));
	irr::core::vector3df balMassComponent = componentThisToBal * ((2 * deltamass / (deltamass + 1)));
	*this->transform->velocity = (componentNormalToBal + thisMassComponent + (*_input->transform->velocity));
	*_input->transform->velocity = (balMassComponent + *_input->transform->velocity);
	this->transform->radii->X = (this->transform->radii->X*2 - this->transform->position->getDistanceFrom(*_input->transform->position));
	_input->transform->radii->X = (this->transform->radii->X);
}