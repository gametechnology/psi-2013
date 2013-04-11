#include "Player.h"
#include "Messages.h"

Player::Player(Composite* parent) : Entity(parent)
{

}

void Player::handleMessage(unsigned int message, void* data) {
	switch(message) {
		/* Do something */
	}
	delete data;
}

Player::~Player()
{
	Entity::~Entity();
}
