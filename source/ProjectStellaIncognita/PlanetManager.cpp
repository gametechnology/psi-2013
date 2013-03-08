#include "PlanetManager.h"

/*
	currently single object, needs to be changed into multiple objects
*/
//void PlanetManager::InitializeMeshes(ISceneManager* smgr, ISceneNode* node, IMesh* mesh)
void PlanetManager::InitializeMeshes(ISceneManager* smgr)
{
	//this->_planetNode = node;
	//this->_planetMesh = mesh;
	this->_sceneManager = smgr;
	this->_scale = 100;
	this->_planetMesh = this->_sceneManager->getMesh("../../assets/Models/Cube.3ds");
	this->_planetMesh->getBoundingBox();
}

void PlanetManager::PlacePlanets()
{
	this->_posX = (rand()%1000+1)-1000;
	this->_posY = (rand()%1000+1)-1000;
	this->_posZ = (rand()%1000+1)-1000;

	this->_planetNode = this->_sceneManager->addMeshSceneNode(this->_planetMesh);
	this->_planetNode->setPosition(vector3df(this->_posX, this->_posY, this->_posZ));
	this->_planetNode->setPosition(vector3df(100,100,100));
	this->_planetNode->setScale(vector3df(this->_scale, this->_scale, this->_scale));
}