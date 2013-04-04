#pragma once
#include "Engine\Game.h"
#include "Engine\Camera.h"
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "Thruster.h"
class WeaponCameraMover : public Component
{
public:
	WeaponCameraMover(Composite* parent);
	~WeaponCameraMover(void);
	void init();
	void update() ;
	void draw(){};
	void handleMessage(unsigned int message, void* data = 0){};
	static matrix4 helmrotation;
	vector3df ownrotation;
	Camera* camera;
};

