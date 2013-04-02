#include "Irrlicht\irrlicht.h"
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

class MainMenuScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	enum MainMenuWindow
	{
		Main = 0,
		Create =1,
		Join = 2
	};

	MainMenuWindow currentWindow;
	// startButton
	// JoinButton

	IGUIEnvironment* guienv;
	

	// create the window where we want to put our controls on.
	IGUIWindow* window;
	
	// add statictext above scrollbar.
	guienv->addStaticText(L"Transparent Control:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, window);
	

	//
	// create a few buttons.
	//
	IGUIButton* createServerButton; = guienv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),window,104, L"Button 1",L"Button 1");
	IGUIButton* joinServerButton; = guienv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),window,105, L"Button 2",L"Button 2");
	IGUIButton* quitButton; = guienv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),window,106, L"Button 3",L"Button 3");
	

};

#endif

