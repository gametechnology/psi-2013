#ifndef PSI_CORE
#define PSI_CORE

#include <Irrlicht/irrlicht.h>
#include "Scene.h"
#include "InputManager.h"
#include "CollisionSystem.h"
#include "Network.h"

typedef irr::IrrlichtDevice IrrDevice;
typedef irr::video::IVideoDriver IrrDriver;
typedef irr::gui::IGUIEnvironment IrrGuiEnv;
typedef irr::scene::ISceneManager IrrSmgr;

class Core
{
private:
	Scene* activeScene;

	IrrDevice* device;
	IrrDriver* driver;
	IrrGuiEnv* guiEnv;
	IrrSmgr* smgr;

	irr::u32 width, height, bitDepth;

	InputManager* appReceiver;
	CollisionSystem* collisionSystem;
public:
	/*!
	* @function Core 
	*	Constructor for the Fancy core. This handles communication with the Irrlicht 3D engine, physics and networking.
	*/
	Core(irr::u32 width, irr::u32 height, irr::u32 bitDepth);
	~Core();

	void draw(irr::u32 alpha, irr::u32 red, irr::u32 green, irr::u32 blue);
	void update(irr::s32 duration);

	void addCustomReceiver(irr::IEventReceiver* receiver);
	void resetReceiver();

	void setActiveScene(Scene* scene);

	IrrDevice* getDevice() { return device; };
	IrrDriver* getDriver() { return driver; };
	IrrGuiEnv* getGuiEnv() { return guiEnv; };
	IrrSmgr* getSmgr() { return smgr; };
	InputManager* getInput() { return appReceiver; };
	Scene* getActiveScene() { return activeScene; };
};

#endif