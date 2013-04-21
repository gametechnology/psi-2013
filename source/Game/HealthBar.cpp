#include "HealthBar.h"
#include "Engine\Game.h"


HealthBar::HealthBar(Composite* parent, vector2df position, int* stat) : Component(parent)
{
	//load the texture of the pip. Pip is a really tiny little bar.
	this->pipTexture_ = Game::driver->getTexture("../../assets/Textures/Stations/HealthPip32.png");
	//make the pip background invisible
	Game::driver->makeColorKeyTexture(pipTexture_, position2d<s32>(0, 0));

	//position of the healthbar and the stat it's following
	HealthBar::position_ = position;
	HealthBar::stat_ = stat;
	HealthBar::visible = true;
}


HealthBar::~HealthBar(void)
{
}

void HealthBar::draw(){
	
	if(visible){
		for(int i = 0; i < *stat_; i++){
			color = SColor(255, 255, 255, 255);
			Game::driver->draw2DImage(
				this->pipTexture_,		//image texture
				rect<s32>(				//draw size and position
					(int)(position_.X + (i / 10) * 32),		//xPosition, every 10 pips it moves 1 to the side.
					(int)(position_.Y + (i % 10) * 8),			//yPosition, every 10 pips it starts back at the top
					32,									//width
					8									//lenght
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
