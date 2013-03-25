#include "Skybox.h"

Skybox::Skybox(Composite* parent) : Entity(parent)
{
	handleTextures(2);
	this->_skyBoxTexture = Game::driver->getTexture(this->_currentTexture);
	this->node = Game::getSceneManager()->addSkyDomeSceneNode(_skyBoxTexture);
}

Skybox::~Skybox()
{
	Entity::~Entity();
}

void Skybox::handleTextures(int curMap)
{
	switch(curMap)
	{
	case 1:
		this->_currentTexture =  "../../assets/Textures/SkyBoxes/skybox01.png";
		break;
	case 2:
		this->_currentTexture =  "../../assets/Textures/SkyBoxes/skybox02.png";
		break;
	case 3:
		break;
	default:
		break;
	}
}