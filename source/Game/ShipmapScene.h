#pragma once
#include "Engine\Scene.h"
#include "Shipmap.h"

class ShipmapScene :
	public Scene
{
private:
	Shipmap _shipmap;
public:
	ShipmapScene(void);
	~ShipmapScene(void);
	virtual void init();
};

