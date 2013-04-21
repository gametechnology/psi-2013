#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"

class Player : public Entity  
{
public:
	Player(Composite* parent);
	~Player();

	int playerID;
	void handleMessage(unsigned int message, void* data = 0);	
};

#endif
