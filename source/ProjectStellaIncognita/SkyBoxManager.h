#ifndef SKYBOXMANAGER_H
#define SKYBOXMANAGER_H

#include "irrlicht.h"
using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class SkyBoxManager
{
	public:
		SkyBoxManager(){};
		~SkyBoxManager(){};
		void loadTexture(ISceneManager* smgr, IVideoDriver* drvr);
		void handleTextures(int curMap);
	private:
		ISceneManager*	_sceneManager;
		IVideoDriver*	_vidDriver;
		ISceneNode*		_skyBox;
		ITexture*		_skyBoxTexture;
		stringw			_currentTexture;
};

#endif // SKYBOXMANAGER_H
