#include <irrlicht.h>

#pragma comment(lib, "Irrlicht.lib")

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;

int main()
{
	// Create the iirlicht device
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(1280, 720), 16, false, false, false, 0);

	// If the device was not created correctly, then shut down the program
	if(!device)
		return 1;

	// Create a driver 
	IVideoDriver* driver = device->getVideoDriver();

	//Set title of the window
	device->setWindowCaption(L"Stella Incognita");

	//Main loop
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,255,255,255));
		driver->endScene();
	}

	device->drop();

	return 0;
}