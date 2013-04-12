#include "Irrlicht\irrlicht.h"

#pragma comment(lib, "Irrlicht.lib")

// Disable DOS window.
#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine\Game.h"
#include "Engine\Network.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

// Predefine static variables
IrrlichtDevice* Game::device;
IVideoDriver* Game::driver;
InputManager* Game::input;
std::forward_list<Scene*>* Game::scenes;

/*Client* Game::client;
Server* Game::server;*/
IGUIEnvironment* Game::guiEnv;

Game::Game()
{
	//Create a new stack to store all scenes
	Game::scenes = new std::forward_list<Scene*>;

	Game::input = new InputManager();

	// Create the irrlicht device 
	Game::device = createDevice(EDT_OPENGL, dimension2d<u32>(1280, 720), 16, false, false, true, Game::input);

	// If the device was not created correctly, then shut down the program
	if(Game::device) {
		// Create a driver 
		driver = Game::device->getVideoDriver();

		//Get the GUI environment
		guiEnv = Game::device->getGUIEnvironment();

		//Set title of the window
		Game::device->setWindowCaption(L"Stella Incognita");
	}

	//client = new Client();
	//client->setupClient("localhost");
	//Game::client = new Client();
	//Game::client->setupClient("localhost");
}

void Game::run()
{
	//Main loop
	while( Game :: device -> run( ) )
	{	
		Game::input->endInputProcess();
		Game :: getCurrentScene( ) -> update( );
		Game :: driver -> beginScene(true, true, SColor(255,100,101,140));
		//Irrlicht draw all
		(*Game::scenes->begin())->sceneManager->drawAll();
		//Game engine draw
		Game::getCurrentScene()->draw();
		//Irrlicht GUI
		Game::guiEnv->drawAll();
		Game::driver->endScene();
		Game::input->startInputProcess();
	}
	Game::device->drop();
}

Scene* Game::getCurrentScene()
{
	return *scenes->begin();
}

ISceneManager* Game::getSceneManager()
{
	return (*scenes->begin())->sceneManager;
}

void Game::addScene(Scene* scene)
{
	Game::scenes->push_front(scene);
	scene->init();
}

void Game::removeScene()
{
	Game::scenes->pop_front();
}

Game::~Game()
{
	//delete messages;
	//for (std::forward_list<Scene*>::iterator i = scenes->begin(); i != scenes->end(); ++i)
	//{
	//	delete (*i);
	//}
	scenes->clear();
	delete scenes;
}
