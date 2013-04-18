#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"
#include "MainMenuEventReceiver.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Player.h"
#include "Engine\Network.h"
 #include <sstream>

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
	void update();
	~MainMenuScene();
	void StartGame();
	 

	//Create the different windows
	MainMenuEventReceiver* eventReceiver;
	IGUIWindow* mainMenuWindow;
	std::list<Player*> playerlist;
	
	//buttons in mainmenu
	IGUIButton* createServerWindow_Button;
	IGUIButton* joinServerWindow_Button;
	IGUIButton* start_button;
	// other items in menu
	IGUIStaticText* Clientlist;
	IGUIEditBox* Ipadresinput;
	IGUIWindow* messagebox;

	//Create a gui environment
	IGUIEnvironment* guiEnv;
	
};

#endif

