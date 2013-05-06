#ifndef CAMERA
#define CAMERA

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class Camera : public IrrlichtNode {
public:
	Camera();
	virtual ~Camera();
	
	irr::scene::ICameraSceneNode* getCameraNode();
	void onAdd();
	void createNode();

	void setTarget(irr::core::vector3df target);
	void setUpVector(irr::core::vector3df up);
private:
	irr::scene::ICameraSceneNode* cameraNode;
};


#endif