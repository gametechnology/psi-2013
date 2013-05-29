#ifndef MAINMENUSCENE
#define MAINMENUSCENE

#include <sstream>

#include <Irrlicht\irrlicht.h>
#include <Engine/Scene.h>
#include <Engine/Network.h>
#include <Engine/NetworkPacket.h>
#include <Engine/INetworkListener.h>
#include <Engine/Interface.h>
#include <Engine/Core.h>

#include "MainMenuEventReceiver.h"
#include "Player.h"
#include "LobbyScene.h"

class MainMenuScene: public Scene, public INetworkListener 
{
public:
	MainMenuScene(Core* core, Interface* ui);
	~MainMenuScene();

	void init();
	void update();

	virtual void requestNextScene();
	virtual void requestPreviousScene();
	virtual void notify(void* data);

	/*
	*INetworkListener override.
	*/
	void handleNetworkMessage(NetworkPacket packet);
private:
	MainMenuEventReceiver* eventReceiver;

	std::list<Player*> playerlist;

	Core* _core;
	Interface* _interface;

	SAppContext context;

	bool nextSceneRequested, nextSceneAllowed;
};

#endif

