#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"
#include "CIrrEventReceiver.h"

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
	~MainMenuScene();

	enum MainMenuState
	{
		Main = 0,
		Create =1,
		Join = 2
	};

	enum Buttons
	{
		JoinServer = 0,
		CreateServer =1,
		Quit = 2
	};

	//Keeps track of which part of the main menu we are in
	MainMenuState mainMenuState;

	//Create a gui environment
	IGUIEnvironment* guiEnv;
	IGUIWindow* window;
	CIrrEventReceiver rv;

	//Buttons
	IGUIButton* createServerButton;
	IGUIButton* joinServerButton;
	IGUIButton* quitButton;
	

};

#endif

