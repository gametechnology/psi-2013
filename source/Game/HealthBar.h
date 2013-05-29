#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include <Engine/Core.h>
#include <Engine/Component.h>
#include <Engine/Composite.h>
#include <Irrlicht/irrlicht.h>

class HealthBar : public Component 
{
public:
	HealthBar(Core*, irr::core::vector2df position, int* stat);
	HealthBar(Core*, irr::core::vector2df position, int* stat, irr::core::vector2df size, int barHeight, irr::video::SColor colour);
	~HealthBar(void);

	void init();
	
	void update();
	void draw();
private:
	Core* _core;

	int* stat_;
	int barHeight_;

	irr::core::vector2df position_;
	irr::core::vector2df size_;	
	irr::video::ITexture* pipTexture_;
	irr::video::SColor color;	
};
#endif
