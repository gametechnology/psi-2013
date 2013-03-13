#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "networking.h"

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
	ServerHandler* server;
	ClientHandler* client;

	server = new ServerHandler();
	client = new ClientHandler();
 
	// Creates device (takes opengl as default driver)
    IrrlichtDevice* device = createDevice(EDT_OPENGL,
            core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

	scene::ISceneNode * node1 = smgr->addSphereSceneNode();
	node1->setPosition(core::vector3df(0,0,50));

	scene::ISceneNode * node2 = smgr->addSphereSceneNode();
	node2->setPosition(core::vector3df(20,0,50));

	// Camera view
	smgr->addCameraSceneNode();

	//game loop
    while(device->run())
    {
		// moving node1
		core::vector3df nodePositionA = node1->getPosition();

        if(receiver.IsKeyDown(irr::KEY_KEY_W))
            nodePositionA.Y += 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePositionA.Y -= 0.01f;

        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            nodePositionA.X -= 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePositionA.X += 0.01f;

		if(receiver.IsKeyDown(irr::KEY_KEY_Z))
            nodePositionA.Z -= 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_Q))
            nodePositionA.Z += 0.01f;

        node1->setPosition(nodePositionA);


		// moving node2
		core::vector3df nodePositionB = node2->getPosition();

        if(receiver.IsKeyDown(irr::KEY_KEY_I))
            nodePositionB.Y += 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_K))
            nodePositionB.Y -= 0.01f;

        if(receiver.IsKeyDown(irr::KEY_KEY_J))
            nodePositionB.X -= 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_L))
            nodePositionB.X += 0.01f;

		if(receiver.IsKeyDown(irr::KEY_KEY_M))
            nodePositionB.Z -= 0.01f;
        else if(receiver.IsKeyDown(irr::KEY_KEY_U))
            nodePositionB.Z += 0.01f;

        node2->setPosition(nodePositionB);

        driver->beginScene(true, true, video::SColor(255,113,113,133));

        smgr->drawAll(); // draw the 3d scene
        driver->endScene();
    }

	device->drop();    
    return 0;
}