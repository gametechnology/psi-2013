#include "HealthBar.h"
#include <iostream>

HealthBar::HealthBar(irr::core::vector2df position, int* stat) : Entity()
{
	//make the pip background invisible
	game->driver->makeColorKeyTexture(pipTexture_, irr::core::position2d<s32>(0, 0));

	//position of the healthbar and the stat it's following
	HealthBar::position_ = position;
	HealthBar::stat_ = stat;
	
	// Use Enable and disable
	//HealthBar::visible = true;

	HealthBar::size_ = irr::core::vector2df(32, 8);
	HealthBar::barHeight_ = 8;
	HealthBar::color = irr::video::SColor(255, 255, 255, 255);
}
HealthBar::HealthBar(irr::core::vector2df position, int* stat, irr::core::vector2df size, int barHeight, irr::video::SColor colour) : Entity()
{
	//position of the healthbar and the stat it's following
	HealthBar::position_ = position;
	HealthBar::stat_ = stat;
	HealthBar::size_ = size;
	HealthBar::barHeight_ = barHeight;
	HealthBar::color = colour;
}

void HealthBar::init() {
	//load the texture of the pip. Pip is a really tiny little bar.
	this->pipTexture_ = game->driver->getTexture("../../assets/Textures/Stations/HealthPip32.png");
	
	//make the pip background invisible
	game->driver->makeColorKeyTexture(pipTexture_, irr::core::position2d<s32>(0, 0));
	
	Entity::init();
}

void HealthBar::draw(){
		std::cout << "stat = " << *stat_ << "\n";
	for(int i = 0; i < *stat_; i++){
		color = irr::video::SColor(255, 255, 255, 255);
		game->driver->draw2DImage(
				this->pipTexture_,						//image texture
				irr::core::rect<s32>(					//draw size and position
				(int)(position_.X + (i / 10) * 32),		//xPosition, every 10 pips it moves 1 to the side.
				(int)(position_.Y + (i % 10) * 8),		//yPosition, every 10 pips it starts back at the top
				32,										//width
				8										//lenght
			),
			irr::core::rect<s32>(0,0,128, 32),			//size of image
			NULL,
			&color,										//this will work great with a white pip~ think of all the fun you could have
			true
		);
	}
		
}

void HealthBar::update(){

}

HealthBar::~HealthBar(void) {

}