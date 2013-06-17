#ifndef CAMERA
#define CAMERA

#include "Engine/IrrlichtNode.h"

using namespace irr;
using namespace core;

class CameraMover;

class Camera : public IrrlichtNode {
public:
	Camera();

	irr::scene::ICameraSceneNode* getCameraNode();

	void onAdd();
	void init();
	void createNode();

	void handleMessage(unsigned int message);

	void update();

	void shake();

	void setTarget(irr::core::vector3df target);
	void setUpVector(irr::core::vector3df up);

private:
	CameraMover* mover;
};

#endif
