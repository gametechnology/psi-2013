#pragma once
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "..\source\Game\Ship.h"

class HealthBar : public Entity {
public:
	HealthBar(vector2df position, int* stat);
	~HealthBar(void);

	void init();
	
	void update();
	void draw();
private:
	int* stat_;
	vector2df position_;
	irr::video::ITexture* pipTexture_;
	SColor color;	
};

