#include <Engine\Composite.h>
#include <iostream>
Composite::Composite() {
	initialized = false;
	destroyed = false;
	enabled = true;
}

Composite::~Composite() {
	
}

void Composite::onAdd() {

}

void Composite::init() {
	initialized = true;
}

void Composite::update() {
	
}

void Composite::lateUpdate() {

}

void Composite::draw() {
	}

void Composite::handleMessage(unsigned int message) {
	
}

void Composite::disable() {
	enabled = false;
}

void Composite::enable() {
	enabled = true;
}
void Composite::destroy(){
	destroyed = true;
}