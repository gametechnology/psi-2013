
#include "WeaponCameraMover.h"
#include "Engine\Entity.h"
#include "Engine\Camera.h"
#include "Ship.h"

WeaponCameraMover::WeaponCameraMover(Composite* parent) : Component(parent)
{
	
}


WeaponCameraMover::~WeaponCameraMover(void)
{


}
void WeaponCameraMover::update(){
	//TODO get input player
	//TODO adjust camera to recieved rotation and input rotation;
	return;
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
	camera->getCameraNode()->setViewMatrixAffector(helmrotation);
	matrix4 calculatedrot;
	calculatedrot.buildRotateFromTo(camera->getCameraNode()->getRotation(), camera->getCameraNode()->getRotation()  + ownrotation);
	camera->getCameraNode()->setViewMatrixAffector(calculatedrot);
}
void WeaponCameraMover::init(){
	
	Ship ship = (Ship*)&parent->parent;
	camera = ship.camera;

}

