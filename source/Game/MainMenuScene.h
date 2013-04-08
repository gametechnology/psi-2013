#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"

#ifndef MAINMENUSCENE
#define MAINMENUSCENE

// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// standard namespace
using namespace std;

class MainMenuScene: public Scene
{
public:
	MainMenuScene();
	virtual void draw();
	void updateLoop();
	~MainMenuScene();

	enum MainMenuState
	{
		Main = 0,
		Create =1,
		Join = 2
	};

	enum ButtonsMainMenu
	{
		CreateServerWindow = 100,
		JoinServerWindow = 101,
		Quit = 102
	};

	enum ButtonsCreateServer
	{
		CreateServer = 200,
		fromCreateToMain = 201,
	};

	enum ButtonsJoinServer
	{
		JoinServer = 300,
		fromJoinToMain = 301
	};

	//Create the different windows
	IGUIWindow* mainMenuWindow;
	IGUIWindow* joinServerWindow;
	IGUIWindow* createServerWindow;
	
	//buttons in mainmenu
	IGUIButton* createServerWindow_Button;
	IGUIButton* joinServerWindow_Button;
	IGUIButton* quit_Button;

	//buttons in create server
	IGUIButton* fromCreateBackToMain_Button;
	IGUIButton* createServer_Button;
	
	//Buttons in Join server
	IGUIButton* joinServer_Button;
	IGUIButton* fromJoinBackToMain_Button;

	//Keeps track of which part of the main menu we are in
	MainMenuState mainMenuState;

	//Create a gui environment
	IGUIEnvironment* guiEnv;
};

#endif

