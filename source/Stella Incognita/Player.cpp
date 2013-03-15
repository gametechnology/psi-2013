#include "Player.h"


Player::Player(Composite* parent) : Entity(parent)
{
	createNode("sydney.md2");
}


Player::~Player()
{
	Entity::~Entity();
}
