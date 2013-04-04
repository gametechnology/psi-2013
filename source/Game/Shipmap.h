#pragma once
#include "Engine\Entity.h"
#include "Shipmap.h"

class Shipmap :
	public Entity
{
private:
	video::ITexture* bg;

public:
	Shipmap(Composite* parent);
	~Shipmap();
	virtual void init();
	void draw();
};

