#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"
#include "Engine/NetworkComponent.h"

class Player : public Entity  {
public:
	//int i;
	//vector3df v3f;
	NetworkComponent* networker;

	Player(Composite* parent);
	~Player();

	void update();
	void handleMessage(unsigned int message, void* data = 0);	
};

#endif
