#ifndef MAINMENUSCENE
#define MAINMENUSCENE

#include <sstream>

#include <Irrlicht\irrlicht.h>
#include <Engine\Game.h>
#include <Engine\Scene.h>
#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>
#include <Engine\INetworkListener.h>

#include "MainMenuEventReceiver.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Player.h"


// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// standard namespace
using namespace std;

class MainMenuScene: public Scene, public INetworkListener {
public:
	MainMenuScene();
	void init();
	void update();
	~MainMenuScene();
	void StartGame();
	void StartTestGame();
	void BackToMainMenu();
	void HandleNetworkMessage(NetworkPacket packet);
	virtual void addGuiElements();

	//Create the different windows
	MainMenuEventReceiver* eventReceiver;
	IGUIWindow* mainMenuWindow;
	std::list<Player*> playerlist;
	
	//buttons in mainmenu
	IGUIButton* createServerWindow_Button;
	IGUIButton* joinServerWindow_Button;
	IGUIButton* start_button;
	IGUIButton* startStatic_button;
	IGUIButton* quit_button;
	IGUIButton* host_quit_button;
	// other items in menu
	IGUIStaticText* Clientlist;
	IGUIStaticText* Namelabel;
	IGUIStaticText* ipLabel;
	IGUIStaticText* waitinglabel;
	IGUIEditBox* Ipadresinput;
	IGUIEditBox* Nameinput;
	IGUIWindow* messagebox;

	//Create a gui environment
	IGUIEnvironment* guiEnv;
	
};

#endif

