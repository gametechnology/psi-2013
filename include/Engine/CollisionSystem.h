#ifndef PSI_COLLISION_SYSTEM
#define PSI_COLLISION_SYSTEM

#include "GameObject.h"

#include <vector>

class CollisionSystem : public Composite
{
public:
	CollisionSystem();

	virtual ~CollisionSystem();

	virtual void update();
	virtual void handleMessage(unsigned int, void* data = 0) { };

	void registerComponent(GameObject* object);
	void unregisterComponent(GameObject* object);
private:
	void narrowPhaseDetection(GameObject* objectA, GameObject* objectB);

	irr::core::vector3df* createBoundingBox(GameObject* object);
	irr::core::vector3df componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity);
};

#endif