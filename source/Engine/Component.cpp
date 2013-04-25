#include <Engine\Component.h>
#include "Engine\Entity.h"

Component::Component() : Composite() {

}

Component::~Component() {

}

Game* Component::getGame() {
	return entity->game;
}

Scene* Component::getScene() {
	return entity->scene;
}

void Component::onAdd() {
	Composite::onAdd();
}

void Component::init() { Composite::init(); }
void Component::update() { Composite::update(); }
void Component::draw() { Composite::draw(); }

void Component::onEnabled() { }
void Component::onDisabled() { }

void Component::handleMessage(unsigned int message) { }