#include "Station.h"


void Station::loadTexture(ISceneManager* smgr, IVideoDriver* drvr) 
{
	this->_sceneManager = smgr;
	this->_vidDriver = drvr;
	
	this->_stationTexture = this->_vidDriver->getTexture("../../assets/Textures/Stations/station_helm.png");
	this->_vidDriver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0,0));
}

void Station::drawTexture()
{
	this->_vidDriver->draw2DImage(this->_stationTexture, position2d<s32>(0,0),rect<s32>(0,0,1280,720),0,SColor(255,255,255,255),true);
}