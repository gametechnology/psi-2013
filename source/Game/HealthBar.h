#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H
#pragma once

#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine/Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"

class HealthBar : public Entity {
public:
	HealthBar(irr::core::vector2df position, int* stat);
	HealthBar(irr::core::vector2df position, int* stat, irr::core::vector2df size, int barHeight, irr::video::SColor colour);
	~HealthBar(void);

	void init();
	
	void update();
	void draw();

private:
	int* stat_;
	irr::core::vector2df position_;
	irr::core::vector2df size_;
	int barHeight_;
	irr::video::ITexture* pipTexture_;
	irr::video::SColor color;	
};
#endif
