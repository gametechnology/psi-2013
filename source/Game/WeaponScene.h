#pragma once
#include "Engine\Scene.h"
#include "net.h"
class WeaponScene : public Scene
{

public:
	
	WeaponScene(void);
	~WeaponScene(void);
	virtual void init();
	Net network;
	Entity* ship;
	Entity* camera;
};

