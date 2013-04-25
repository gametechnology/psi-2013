#include "HealthBar.h"
#include <iostream>

HealthBar::HealthBar(Composite* parent, vector2df position, int* stat) : Component(parent)
{
	//load the texture of the pip. Pip is a really tiny little bar.
	this->pipTexture_ = Game::driver->getTexture("../assets/Textures/Stations/HealthPip32.png");
	//make the pip background invisible
	Game::driver->makeColorKeyTexture(pipTexture_, position2d<s32>(0, 0));

	//position of the healthbar and the stat it's following
	HealthBar::position_ = position;
	HealthBar::stat_ = stat;
	HealthBar::visible = true;
	HealthBar::size_ = vector2df(32, 8);
	HealthBar::barHeight_ = 8;
	HealthBar::color = SColor(255, 255, 255, 255);
}
HealthBar::HealthBar(Composite* parent, vector2df position, int* stat, vector2df size, int barHeight, SColor colour) : Component(parent)
{
	//load the texture of the pip. Pip is a really tiny little bar.
	this->pipTexture_ = Game::driver->getTexture("../assets/Textures/Stations/HealthPip32.png");
	//make the pip background invisible
	Game::driver->makeColorKeyTexture(pipTexture_, position2d<s32>(0, 0));

	//position of the healthbar and the stat it's following
	HealthBar::position_ = position;
	HealthBar::stat_ = stat;
	HealthBar::visible = true;
	HealthBar::size_ = size;
	HealthBar::barHeight_ = barHeight;
	HealthBar::color = colour;
}


HealthBar::~HealthBar(void)
{
}

void HealthBar::draw(){
	if(visible){
		std::cout << "stat = " << *stat_ << "\n";
		for(int i = 0; i < *stat_; i++){
			vector2df pipos = vector2df((f32)(position_.X + (i / barHeight_) * size_.X), (f32)(position_.Y + (i % barHeight_) *  size_.Y));
			
			Game::driver->draw2DImage(
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

void HealthBar::update(){

}

void HealthBar::init(){

}
