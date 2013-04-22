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
	if (entity->initialized)
		init();
}

void Component::init() {

}

void Component::update() {

}

void Component::draw() {

}

void Component::handleMessage(unsigned int message) {

}