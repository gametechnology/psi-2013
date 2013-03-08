#include "SkyBoxManager.h"


void SkyBoxManager::loadTexture(ISceneManager* smgr, IVideoDriver* drvr) 
{
	this->_sceneManager = smgr;
	this->_vidDriver = drvr;
	
	this->handleTextures(2);
	this->_skyBoxTexture = this->_vidDriver->getTexture(this->_currentTexture);
	this->_skyBox = this->_sceneManager->addSkyDomeSceneNode(_skyBoxTexture);
}

void SkyBoxManager::handleTextures(int curMap)
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