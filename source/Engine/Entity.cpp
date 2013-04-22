#include <Engine\Entity.h>
#include "Engine\Component.h"
#include "Engine\Transform.h"

Entity::Entity() : Composite() {
 transform = new Transform();
 addComponent(transform);
}
Entity::~Entity(){

}
void Entity::onAdd() {
 for (unsigned int i = 0; i < components.size(); i++) {
  components[i]->onAdd();
 }

 for (unsigned int i = 0; i < children.size(); i++) {
  children[i]->onAdd();
 }

 // If this is true, it means the object is added during runtime, and will miss the base initialize.
 // Therefore initialize it after it has been added.
 if (parent != NULL && parent->initialized) {
  init();
 }
}

void Entity::init() {
 for (unsigned int i = 0; i < components.size(); i++) {
  components[i]->init();
 }

 for (unsigned int i = 0; i < children.size(); i++) {
  children[i]->init();
 }
}

void Entity::handleMessage(unsigned int message) {
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
 for (unsigned int i = 0; i < components.size(); i++) {
  if (components[i] == NULL) {
   components.erase(components.begin()+i--);
  } else if (components[i]->destroyed) {
    Component* component = components[i];
    components.erase(components.begin()+i--);
    delete component;
  } else {
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
   children[i]->update();
  }
 }
}

void Entity::lateUpdate() {
 for (unsigned int i = 0; i < components.size(); i++) {
  components[i]->lateUpdate();
 }

 for (unsigned int i = 0; i < children.size(); i++) {
  children[i]->lateUpdate();
 }
}

void Entity::draw() {
 for (unsigned int i = 0; i < components.size(); i++) {
  components[i]->draw();
 }

 for (unsigned int i = 0; i < children.size(); i++) {
  children[i]->draw();
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

   delete component;
   return true;
  }
 }

 return false;
}

void Entity::addChild(Entity* child) {
 children.push_back(child);
 child->parent = this;

 child->onAdd();
}

bool Entity::removeChild(Entity* child) {
 for (unsigned int i = 0; i < components.size(); i++) {
  if (children[i] == child) {
   children[i] = NULL;
   return true;
  }
 }

 return false;
}