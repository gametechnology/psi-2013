#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"

class Player : public Entity  {
public:
	Player(Composite* parent);
	~Player();
	const wchar_t* Name;
	int Team;
	void handleMessage(unsigned int message, void* data = 0);	
};

#endif
