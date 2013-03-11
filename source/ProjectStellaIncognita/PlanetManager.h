#ifndef PLANETMANAGER_H
#define PLANETMANAGER_H

#include "irrlicht.h"
using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class PlanetManager
{
	public:
		PlanetManager(){};
		~PlanetManager(){};
		void InitializeMeshes(ISceneManager* smgr, ISceneNode* node, IMesh* mesh);
		void InitializeMeshes(ISceneManager* smgr);
		void PlacePlanets();
	private:
		IMesh*			_planetMesh[8];
		ISceneNode*		_planetNode[20];
		ISceneManager* _sceneManager;
		unsigned		_scale;
		signed			_posX;
		signed			_posY;
		signed			_posZ;
};
#endif