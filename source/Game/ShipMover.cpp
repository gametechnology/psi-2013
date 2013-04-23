#include "ShipMover.h"

ShipMover::ShipMover(Ship* parent) : BasicMoverComponent() {
	maxFwdSpeed = 10;
	maxBwdSpeed = -10;
}

ShipMover::~ShipMover() {

}

void ShipMover::update() {
	if (Game::input->isKeyboardButtonDown(KEY_KEY_R) && thrust < maxFwdSpeed)
		thrust += 0.01f;
	if (Game::input->isKeyboardButtonDown(KEY_KEY_F) && thrust > maxBwdSpeed)
		thrust -= 0.01f;

	BasicMoverComponent::update();
}