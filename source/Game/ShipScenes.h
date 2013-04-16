#pragma once
#include "Engine\Scene.h"

class ShipScenes :
	public Scene
{
public:
	ShipScenes(void);
	~ShipScenes(void);
	void init();

	Entity* ship;
	Entity* camera;
};

