#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"
#include "MainMenuEventReceiver.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Player.h"
#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"
 #include <sstream>
#include "Engine\INetworkListener.h"

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

class MainMenuScene: public Scene, public INetworkListener
{
public:
	MainMenuScene();
	void update();
	~MainMenuScene();
	void StartGame();
	void HandleNetworkMessage(NetworkPacket packet); 

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
	IGUIStaticText* Namelabel;
	IGUIEditBox* Ipadresinput;
	IGUIEditBox* Nameinput;
	IGUIWindow* messagebox;

	//Create a gui environment
	IGUIEnvironment* guiEnv;
	
};

#endif

