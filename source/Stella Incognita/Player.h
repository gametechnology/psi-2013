/*
	Example entity for loading a model
*/

#ifndef PLAYER
#define PLAYER

#include "Entity.h"
class Player : public Entity  {
public:
	Player(Composite* parent);
	virtual ~Player();
};

#endif
