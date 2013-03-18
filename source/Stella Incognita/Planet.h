/*
	Example entity for loading a model
*/

#ifndef PLANET
#define PLANET

#include "Entity.h"
class Planet : public Entity  {
public:
	Planet(Composite* parent);
	virtual ~Planet();
};

#endif