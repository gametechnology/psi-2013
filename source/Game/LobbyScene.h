#ifndef LOBBY_SCENE
#define LOBBY_SCENE

#include <Engine/Core.h>
#include <Engine/Interface.h>
#include <Engine/Scene.h>
#include <Engine/INetworkListener.h>

#include <list>
#include <sstream>

#include "MainMenuEventReceiver.h"
#include "Player.h"

class LobbyScene : public Scene, public INetworkListener
{
public:
	LobbyScene(Core* core, Interface* ui);
	~LobbyScene();

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
};

#endif