#include <Engine/PrimitiveComponent.h>

using namespace irr;
using namespace irr::scene;
using namespace irr::core;

PrimitiveComponent::PrimitiveComponent(ISceneManager* smgr, PrimitiveType type, f32 size, vector3df position) 
	: Component("Primitive")
{
	this->smgr = smgr;

	switch(type)
	{
	case PRIM_CUBE:
		createCubePrimitive(size, position);
		break;
	case PRIM_SPHERE:
		createSpherePrimitive(size, position);
		break;
	}
}

PrimitiveComponent::PrimitiveComponent(ISceneManager* smgr, PrimitiveType type, f32 size, ISceneNode* parent, vector3df relativePosition) 
	: Component("Primitive")
{
	this->smgr = smgr;

	switch(type)
	{
	case PRIM_CUBE:
		createCubePrimitive(size, relativePosition);
		break;
	case PRIM_SPHERE:
		createSpherePrimitive(size, relativePosition);
		break;
	}
}

PrimitiveComponent::~PrimitiveComponent()
{
	smgr->addToDeletionQueue(node);
	smgr = NULL;
}


void PrimitiveComponent::createCubePrimitive(f32 size, vector3df position)
{
	node = smgr->addCubeSceneNode(size, 0, 1, position);
}

void PrimitiveComponent::createSpherePrimitive(f32 radius, vector3df position)
{
	node = smgr->addSphereSceneNode(radius, 16, 0, 2, position);
}