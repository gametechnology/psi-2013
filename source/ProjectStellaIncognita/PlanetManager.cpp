#include "PlanetManager.h"

/*
	currently single object, needs to be changed into multiple objects
*/
void PlanetManager::InitializeMeshes(ISceneManager* smgr)
{
	this->_sceneManager = smgr;
	this->_scale = 100;
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
	this->_posX = (rand()%1000+1)-1000;
	this->_posY = (rand()%1000+1)-1000;
	this->_posZ = (rand()%1000+1)-1000;

	bool rerun = true;
	 unsigned i = 0;
	 while (rerun)
	 {
		 this->_planetNode[i] = this->_sceneManager->addMeshSceneNode(this->_planetMesh[rand() % 3+1]);
		signed v1 = (rand() % 1000 + 1)-1000;
		signed v2 = (rand() % 1000 + 1)-1000;
		signed v3 = (rand() % 1000 + 1)-1000;
		this->_planetNode[i]->setPosition(vector3df(v1,v2,v3));
		this->_planetNode[i]->setScale(vector3df(this->_scale, this->_scale, this->_scale));
	
		if (i+1>=20)
		{
			rerun = false;
		}
		i++;
	 }
}