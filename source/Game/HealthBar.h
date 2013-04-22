#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H
#pragma once

#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine/Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"

class HealthBar : public Component
{
public:
	HealthBar(Composite* parent, vector2df position, int* stat);
	HealthBar(Composite* parent, vector2df position, int* stat, vector2df size, int barHeight);
	~HealthBar(void);
	void update();
	void draw();
	void init();
	bool visible;
private:
	int* stat_;
	vector2df position_;
	vector2df size_;
	int barHeight_;
	irr::video::ITexture* pipTexture_;
	SColor color;	
};
#endif
