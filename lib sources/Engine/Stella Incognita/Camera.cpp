#include "Camera.h"
#include "Game.h"
#include "CameraMover.h"


Camera::Camera(Composite* parent, vector3df position, vector3df lookAt):Entity(parent)
{
	if (parent != NULL && dynamic_cast<Entity*>(parent) != NULL)
		parentIsEntity = true;
	else parentIsEntity = false; 
	node = Game::getSceneManager()->addCameraSceneNode(NULL, position, lookAt);
	addComponent(new CameraMover(this));
}

irr::scene::ICameraSceneNode* Camera::getCameraNode()
{
	return ((irr::scene::ICameraSceneNode*)(node));
}

Entity* Camera::getEntity()
{
	if (parentIsEntity)
		return (Entity*)(parent);
	else return NULL;
}

Camera::~Camera()
{
	Entity::~Entity();
}
