#include "PlanetManager.h"

void PlanetManager::InitializeMeshes(ISceneManager* smgr)
{
	this->_sceneManager = smgr;
	this->_scale = 15;
	this->_planetMesh[0] = smgr->getMesh("../../assets/Models/floor.3ds");
	this->_planetMesh[1] = smgr->getMesh("../../assets/Models/Cube.3ds");
	this->_planetMesh[2] = smgr->getMesh("../../assets/Models/teapot.3ds");
	this->_planetMesh[3] = smgr->getMesh("../../assets/Models/UnknownAst.3ds");
	this->_planetMesh[0]->getBoundingBox();
	this->_planetMesh[1]->getBoundingBox();
	this->_planetMesh[2]->getBoundingBox();
	this->_planetMesh[3]->getBoundingBox();
}

void PlanetManager::PlacePlanets()
{
//	this->_planetNode[0] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[0]);
//	this->_posX = 0;
//	this->_posY = 0;
//	this->_posZ = 0;
//	this->_planetNode[0]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
//	this->_planetNode[0]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[1] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[3]);
	this->_posX = 20;
	this->_posY = 0;
	this->_posZ = 20;
	this->_planetNode[1]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[1]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[2] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[2]);
	this->_posX = 1000;
	this->_posY = 100;
	this->_posZ = 1000;
	this->_planetNode[2]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[2]->setScale(vector3df(this->_scale, this->_scale, this->_scale));
	this->_planetNode[2]->setRotation(vector3df(0,90,0));

	this->_planetNode[3] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = 0;
	this->_posY = 0;
	this->_posZ = 1000;
	this->_planetNode[3]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[3]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[4] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = 0;
	this->_posY = 1000;
	this->_posZ = 0;
	this->_planetNode[4]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[4]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[5] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = 1000;
	this->_posY = 0;
	this->_posZ = 0;
	this->_planetNode[5]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[5]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[6] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = 0;
	this->_posY = 0;
	this->_posZ = -1000;
	this->_planetNode[6]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[6]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[7] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = 0;
	this->_posY = -1000;
	this->_posZ = 0;
	this->_planetNode[7]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[7]->setScale(vector3df(this->_scale, this->_scale, this->_scale));

	this->_planetNode[8] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[1]);
	this->_posX = -1000;
	this->_posY = 0;
	this->_posZ = 0;
	this->_planetNode[8]->setPosition(vector3df(this->_posX,this->_posY,this->_posZ));
	this->_planetNode[8]->setScale(vector3df(this->_scale, this->_scale, this->_scale));
}

void PlanetManager::LetThereBeLights(ISceneManager* smgr)
{
//	this->_light[0] = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
//	this->_light[1] = smgr->addLightSceneNode(0,vector3df(-5000,-5000,-5000),SColor(100,100,100,255),100000);
//	this->_light[2] = smgr->addLightSceneNode(0,vector3df(0,0,0),SColor(100,100,100,255),100000);
	this->_light[3] = smgr->addLightSceneNode(0,vector3df(5000,0,0),SColor(100,100,100,255),100000);
	this->_light[4] = smgr->addLightSceneNode(0,vector3df(0,5000,0),SColor(100,100,100,255),100000);
	this->_light[5] = smgr->addLightSceneNode(0,vector3df(0,0,5000),SColor(100,100,100,255),100000);
	this->_light[6] = smgr->addLightSceneNode(0,vector3df(-5000,0,0),SColor(100,100,100,255),100000);
	this->_light[7] = smgr->addLightSceneNode(0,vector3df(0,-5000,0),SColor(100,100,100,255),100000);
	this->_light[8] = smgr->addLightSceneNode(0,vector3df(0,0,-5000),SColor(100,100,100,255),100000);
}