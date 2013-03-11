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
		void LetThereBeLights(ISceneManager* smgr);
	private:
		IMesh*				_planetMesh[8];
		ISceneNode*			_planetNode[20];
		ILightSceneNode*	_light[20];
		ISceneManager*		_sceneManager;
		unsigned			_scale;
		float				_posX;
		float				_posY;
		float				_posZ;
};
#endif