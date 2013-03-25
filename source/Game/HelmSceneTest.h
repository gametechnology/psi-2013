#pragma once
#include "Engine\Scene.h"
class HelmSceneTest :
	public Scene
{
public:
	HelmSceneTest(void);
	~HelmSceneTest(void);
	virtual void init();

	Entity* ship;
	Entity* camera;
};

