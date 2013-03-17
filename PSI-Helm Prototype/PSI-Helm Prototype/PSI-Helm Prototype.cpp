
#include "stdafx.h"
using namespace std;

#include <irrlicht.h>
#include "driverChoice.h"
#include "StandardObject.h"
#include "GameScreen.h"
#include "BasicObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
private:
};

int main()
{
	
	MyEventReceiver rv;
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(1680, 1050), 16,
			true, false, false, &rv);
	//device->setEventReceiver(rv);
	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	device->getCursorControl()->setVisible(false);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	// Lets look how the standardObject works
	StandardObject::smgr = smgr;
	StandardObject::driver = driver;
	BasicObject::smgr = smgr;
	BasicObject::driver = driver;

	GameScreen::smgr = smgr;
	GameScreen::driver = driver;
	GameScreen::guienv = guienv;
	GameScreen gameScreen = GameScreen();
	
	u32 then = device->getTimer()->getTime();
	while(device->run())
	{
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		gameScreen.Update(rv.KeyIsDown, frameDeltaTime);
		driver->endScene();
	}

	device->drop();

	return 0;
}
