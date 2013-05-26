#ifndef PSI_COLLISION_COMPONENT
#define PSI_COLLISION_COMPONENT

#include "Component.h"
#include <vector>

class CollisionComponent : public Component
{
public:
	CollisionComponent();
	~CollisionComponent();

	void narrowPhaseDetection(Component* _input);
	irr::core::vector3df static componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity);
};

#endif