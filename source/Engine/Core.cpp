#include <Engine/Core.h>

using namespace irr;
using namespace irr::core;
using namespace irr::video;

Core::Core(u32 width, u32 height, u32 bitDepth)
{
	this->width = width;
	this->height = height;
	this->bitDepth = bitDepth;
	
	appReceiver = new InputManager();
	collisionSystem = new CollisionSystem();

	device = createDevice(EDT_OPENGL, dimension2d<u32>(width, height), bitDepth, false, false, true, appReceiver);

	if (!device)
		exit(1);

	driver = device->getVideoDriver();
	guiEnv = device->getGUIEnvironment();
	smgr = device->getSceneManager();

	activeScene = NULL;
}

Core::~Core()
{
	device = NULL;
	driver = NULL;
	guiEnv = NULL;
	smgr = NULL;
	activeScene = NULL;
}

void Core::draw(u32 alpha, u32 red, u32 green, u32 blue)
{
	driver->beginScene(true, true, video::SColor(alpha, red, green, blue));
	smgr->drawAll();
	guiEnv->drawAll();
	activeScene->draw();
	driver->endScene();
}

void Core::update(s32 duration)
{
	collisionSystem->update();
	activeScene->update();

	Network::GetInstance()->DistributeReceivedPackets();
}

void Core::addCustomReceiver(irr::IEventReceiver* receiver)
{
	appReceiver->setCustomEventReceiver(receiver);
}

void Core::resetReceiver()
{
	appReceiver->unsetCustomEventReceiver();
}

void Core::setActiveScene(Scene* scene)
{
	if(activeScene != NULL)
		delete activeScene;

	activeScene = scene;
	activeScene->init();
}