

#include <irrlicht.h>
#include "StandardObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef GAMESCREEN_H
#define GAMESCREEN_H
class GameScreen {
public:

	GameScreen();
	static ISceneManager* smgr;
	static IVideoDriver* driver;
	static IGUIEnvironment* guienv;
	
	StandardObject* flag;
	gui::IGUIFont* font;
	video::ITexture* images;
	void Update(bool input[],f32 deltaTime);

private:
};
#endif