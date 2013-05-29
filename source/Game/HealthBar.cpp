#include "HealthBar.h"
#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::video;

HealthBar::HealthBar(Core* core, vector2df position, int* stat) : Component("HealthBar")
{
	_core = core;
	//position of the healthbar and the stat it's following
	position_ = position;
	stat_ = stat;

	size_ = irr::core::vector2df(32, 8);
	barHeight_ = 8;
	color = irr::video::SColor(255, 255, 255, 255);

	setEnabled(true);
}

HealthBar::HealthBar(Core* core, vector2df position, int* stat, vector2df size, int barHeight, SColor colour) : Component("HealthBar")
{
	_core = core;
	//position of the healthbar and the stat it's following
	position_ = position;
	stat_ = stat;

	size_ = size;
	barHeight_ = barHeight;
	color = colour;

	setEnabled(true);
}

void HealthBar::init() 
{
	//load the texture of the pip. Pip is a really tiny little bar.
	pipTexture_ = _core->getDriver()->getTexture("../assets/Textures/Stations/HealthPip32.png");

	//make the pip background invisible
	_core->getDriver()->makeColorKeyTexture(pipTexture_, position2d<s32>(0, 0));

	Component::init();
}

void HealthBar::draw()
{
	if(isEnabled()){
		//std::cout << "stat = " << *stat_ << "\n";
		for(int i = 0; i < *stat_; i++){
			vector2df pipos = vector2df((f32)(position_.X + (i / barHeight_) * size_.X), (f32)(position_.Y + (i % barHeight_) *  size_.Y));

			_core->getDriver()->draw2DImage(
				this->pipTexture_,		//image texture
				rect<s32>(				//draw size and position
				(s32)pipos.X,		//xPosition, every 10 pips it moves 1 to the side.
				(s32)pipos.Y,			//yPosition, every 10 pips it starts back at the top
				(s32)pipos.X + size_.X,									//width
				(s32)pipos.Y  + size_.Y									//lenght
				),
				rect<s32>(0,0,128, 32),	//size of image
				NULL,
				&color,					//this will work great with a white pip~ think of all the fun you could have
				true
				);	
		}
	}
}

void HealthBar::update()
{

}

HealthBar::~HealthBar() 
{

}