#ifndef COLLISIONSYSTEM
#define COLLISIONSYSTEM

#include "Engine\Component.h"
#include "Engine\Entity.h"

class CollisionSystem
{
public:

	CollisionSystem();
	virtual ~CollisionSystem();
	virtual void update();
	void addListener(Entity* entity);
	void removeListener(Entity* entity);

private:
	std::vector<Entity*> listeners;
	void handleCollision();
	bool isNotAdded(Entity* entity);
};

#endif