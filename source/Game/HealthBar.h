#pragma once
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "..\source\Game\Ship.h"

class HealthBar :
	public Component
{
public:
	HealthBar(Composite* parent, vector2df position, int* stat);
	~HealthBar(void);
	void update();
	void draw();
	void init();
	bool visible;
private:
	int* stat_;
	vector2df position_;
	irr::video::ITexture* pipTexture_;
	SColor color;	
};

