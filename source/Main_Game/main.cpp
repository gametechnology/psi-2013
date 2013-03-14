#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "MainEventReceiver.cpp";
#include "NetworkBoy.h";

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

class MyEventReceiver : public IEventReceiver {
public:
    // On event take input
    virtual bool OnEvent(const SEvent& event) {
        // Saves the state of each key (pressed down or not)
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // Check if a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver() {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // This array is used to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main() {
    // create device
    MyEventReceiver receiver;

	// Creates device (takes opengl as default driver)
    IrrlichtDevice* device = createDevice(EDT_OPENGL,
            core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	irr::gui::IGUIButton* connectButton = guienv->addButton(rect<s32>(10, 120, 110, 120+32), 0, GUI_ID_CONNECT_BUTTON, L"Connect");
	irr::gui::IGUIEditBox* ipBox = guienv->addEditBox(L"", rect<s32>(10, 80, 200, 100));

	// create our network interface
	NetworkBoy networkBoy;

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.networkBoy = &networkBoy;
	context.ipBox = ipBox;
	context.connect = connectButton;

	// Then create the event receiver, giving it that context structure.
	MainEventReceiver guiReceiver(context);
	device->setEventReceiver(&guiReceiver);

	// Camera view
	smgr->addCameraSceneNode();

	//game loop
    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(255,113,113,133));

        smgr->drawAll(); // draw the 3d scene
		guienv->drawAll(); // draw the ui
        driver->endScene();
    }

	device->drop();    
    return 0;
}