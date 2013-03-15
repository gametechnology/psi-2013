#include "Camera.h"
#include "Game.h"


Camera::Camera(Composite* parent):Entity(parent)
{
	if (parent != NULL && dynamic_cast<Entity*>(parent) != NULL)
		parentIsEntity = true;
	else parentIsEntity = false; 
	node = Game::getSceneManager()->addCameraSceneNode();
}

irr::scene::ICameraSceneNode* Camera::getCameraNode()
{
	return ((irr::scene::ICameraSceneNode*)(node));
}

void Camera::update()
{
	
	position = node->getPosition();
	orientation = node->getRotation();
	if (this->parentIsEntity)
	{
		position -= oldParentPosition;
		orientation -= oldParentOrientation;
		position += ((Entity*)(parent))->position;
		orientation += ((Entity*)(parent))->orientation;
	}
	Entity::update();
}

Camera::~Camera()
{
	Entity::~Entity();
}
