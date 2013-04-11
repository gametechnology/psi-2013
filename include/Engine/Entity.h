#include "Engine\Composite.h"
#include "Irrlicht\irrlicht.h"
#include "Irrlicht\vector3d.h"
#include "Irrlicht\irrMath.h"
#include <string>

#ifndef ENTITY
#define ENTITY

using namespace irr;
using namespace core;

class Entity : public Composite
{
public:
	Entity();
	virtual ~Entity();

	// Variables
	irr::scene::ISceneNode* node;

	float mass;
	vector3d<float> force;
	vector3d<float> position;
	vector3d<float> velocity;
	vector3d<float> accelaration;
	vector3d<float> orientation;
	vector3d<float> angularVelocity;
	vector3d<float> angularAccelaration;

	vector3d<float> anchorPoint;
	bool visible;

	// Methods
	virtual void update();
	virtual void draw();
	virtual void createNode(std::string modelPath);
};

#endif
