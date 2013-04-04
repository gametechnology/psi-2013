
#include "WeaponCameraMover.h"
#include "Engine\Entity.h"
#include "Engine\Camera.h"
#include "Ship.h"

WeaponCameraMover::WeaponCameraMover(Composite* parent) : Component(parent)
{

	camera =  ((Ship*)parent->parent)->camera;
}


WeaponCameraMover::~WeaponCameraMover(void)
{


}
void WeaponCameraMover::update(){
	//TODO get input player
	//TODO adjust camera to recieved rotation and input rotation;
	
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
	
	camera->getCameraNode()->setRotation(helmrotation + ownrotation);
}
void WeaponCameraMover::init(){
	
	

}

