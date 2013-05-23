#ifndef WEAPONCAMERA
#define WEAPONCAMERA

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class WeaponCamera: public IrrlichtNode {
public:
	WeaponCamera();
	~WeaponCamera();

	irr::scene::ICameraSceneNode* getCameraNode();

	void init();
	void createNode();

	void update();

	void setTarget(irr::core::vector3df target);
	void setUpVector(irr::core::vector3df up);
};
#endif