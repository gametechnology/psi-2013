#pragma once
#include "Engine\Scene.h"
#include "net.h"
class HelmSceneTest : public Scene
{

public:
	
	HelmSceneTest(void);
	~HelmSceneTest(void);
	virtual void init();
	Net network;
	Entity* ship;
	Entity* camera;
};

