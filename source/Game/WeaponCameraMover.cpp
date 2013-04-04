#include "WeaponCameraMover.h"
#include "Engine\Entity.h"
#include "Engine\Camera.h"
#include "Ship.h"
#include "Engine\Input.h"

#define ANGLESPEED 0.5f;

WeaponCameraMover::WeaponCameraMover(Composite* parent) : Component(parent)
{

	camera =  ((Ship*)parent->parent)->camera;
	//input = ((Ship*)parent->parent)->input;
	WeaponCameraMover::input = &eventReceiver;
}


WeaponCameraMover::~WeaponCameraMover(void)
{


}

void WeaponCameraMover::update(){
	//get input player
	if(Input::KeyIsDown[KEY_KEY_W]){
		ownrotation.X += ANGLESPEED;
		//std::cout << "W is pressed" << std::endl;
	}
	if(Input::KeyIsDown[KEY_KEY_Z]){
		ownrotation.X -= ANGLESPEED;
	}
	if(Input::KeyIsDown[KEY_KEY_E]){
		ownrotation.Y += ANGLESPEED;
	}
	if(Input::KeyIsDown[KEY_KEY_X]){
		ownrotation.Y -= ANGLESPEED;
	}
	if(Input::KeyIsDown[KEY_KEY_R]){
		ownrotation.Z += ANGLESPEED;
	}
	if(Input::KeyIsDown[KEY_KEY_C]){
		ownrotation.Z -= ANGLESPEED;
	}

	//get the constraints for the view
	if(ownrotation.X > 90)
		ownrotation.X = 90;
	if(ownrotation.X < -90)
		ownrotation.X = -90;
	if(ownrotation.Y > 90)
		ownrotation.Y = 90;
	if(ownrotation.Y < -90)
		ownrotation.Y = -90;
	if(ownrotation.Z > 90)
		ownrotation.Z = 90;
	if(ownrotation.Z < -90)
		ownrotation.Z = -90;
	
	//adjust camera to recieved rotation and input rotation;
	camera->getCameraNode()->setRotation(helmrotation + ownrotation);
}
void WeaponCameraMover::init(){

}

