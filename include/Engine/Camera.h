#include "Entity.h"



#ifndef CAMERA

#define CAMERA



using namespace irr;

using namespace core;



class Camera : public Entity

{

public:
	
	Camera(Composite* parent, vector3df position = vector3df(0, 0, 0), vector3df lookAt = vector3df(0, 0, 100));

	virtual ~Camera();



	irr::scene::ICameraSceneNode* getCameraNode();

	Entity* getEntity();

	bool parentIsEntity;
private:
}
;



#endif