#ifndef COLLISIONCOMPONENT
#define COLLISIONCOMPONENT

#include "Irrlicht\irrlicht.h"
#include "Engine\Component.h"
#include "Engine\Entity.h"

class Collision : public Component
{
public:
	Collision(void);
	virtual ~Collision(void);

	virtual void onAdd();

	void static NarrowPhaseDetection(vector<Entity*> _input);
	irr::core::vector3df static componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity);
};

#endif