#include "Player.h"
#include "Messages.h"

Player::Player(Composite* parent) : Entity(parent)
{
	createNode("../assets/sydney.md2");
}

void Player::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case DAMAGE: /* Do something */;
	}
	delete data;
}

Player::~Player()
{
	Entity::~Entity();
}
