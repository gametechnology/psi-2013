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
struct host{
	int id;
	wchar_t* name;
	std::string ipadress;
};

class MainMenuScene: public Scene, public INetworkListener {
public:
	MainMenuScene();
	void init();
	void update();
	~MainMenuScene();
	void StartGame();
	void StartTestGame();
	void BackToMainMenu();
	static void serverlistreciever(void * menu);
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
	IGUIButton* findserver_Button;
	// other items in menu
	std::list<IGUIElement*> lisitems;
	std::list<host> hostlist;
	IGUIStaticText* Clientlist;
	IGUIStaticText* Namelabel;
	IGUIStaticText* servernameLabel;
	IGUIStaticText* ipLabel;
	IGUIStaticText* waitinglabel;

	IGUIStaticText* servernames;	
	IGUIStaticText*	serverip;
	IGUIStaticText*	serveractions;	
	IGUIEditBox* Ipadresinput;
	IGUIEditBox* servernameInput;
	IGUIEditBox* Nameinput;
	IGUIWindow* messagebox;
	bool issearching;
	//Create a gui environment
	IGUIEnvironment* guiEnv;
	
};

#endif

