/*
	Example entity for loading a model
*/

#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"
class Player : public Entity  {
public:
	unsigned int radius_;
	Player(Composite* parent);
	void Player::handleMessage(unsigned int message, void* data = 0);
	virtual ~Player();
};

#endif
