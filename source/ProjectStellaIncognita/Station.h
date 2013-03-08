#ifndef STATION_H
#define STATION_H

#include "irrlicht.h"
using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Station
{
	public:
		Station(){};
		~Station(){};
		void loadTexture(ISceneManager* smgr, IVideoDriver* drvr);
		void drawTexture();
	private:
		ISceneManager*	_sceneManager;
		IVideoDriver*	_vidDriver;
		ITexture*		_stationTexture;
};

#endif // STATION_H
