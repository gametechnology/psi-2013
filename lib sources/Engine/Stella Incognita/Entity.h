#include "Composite.h"
#include "irrlicht.h"
#include <vector3d.h>
#include "irrMath.h"

#ifndef ENTITY
#define ENTITY

using namespace irr;
using namespace core;

class Entity : Composite
{
public:
	Entity();
	~Entity();

	// Variables
	vector3d<float> position;
	vector3d<float> velocity;
	vector3d<float> accelaration;
	vector3d<float> orientation;
	vector3d<float> orientationVelocity;
	vector3d<float> orientationAccelaration;

	// Methods
	virtual void Update();
	virtual void Draw();

	
};

#endif
