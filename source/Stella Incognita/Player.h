/*
	Example entity for loading a model
*/

#ifndef PLAYER
#define PLAYER

#include "Entity.h"
class Player : public Entity  {
public:
	Player(Composite* parent);
	void Player::handleMessage(unsigned int message, void* data = 0);
	virtual ~Player();
};

#endif
