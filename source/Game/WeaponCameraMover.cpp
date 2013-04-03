
#include "WeaponCameraMover.h"
#include "Engine\Entity.h"
#include "Engine\Camera.h"

WeaponCameraMover::WeaponCameraMover(Composite* parent) : Component(parent)
{
	
}


WeaponCameraMover::~WeaponCameraMover(void)
{


}
void WeaponCameraMover::update(){
	//TODO get input player
	//TODO check if own camera raotation is within bounds.
	//TODO adjust camera to recieved rotation and input rotation;
}
void WeaponCameraMover::init(){
	// TODO get camera
}

