#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"
#include "MapGenerator.h"
#include "MainMenuScene.h"
#include "Engine/Network.h"
#include "../../include/SFML/Network.hpp"
#include "Engine/NetworkPacket.h"
#include <enet\enet.h>

// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main()
{
	// Create engine
	Game game = Game();

	//Game::client->setupClient("145.92.13.97");

	//Code to create the GalaxyMap
	/*MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));*/

	//Game::client->setupClient("145.92.13.97");

	Network::GetInstance()->InitializeServer();

	unsigned int data1 = 1;
	std::string data2 = "hello";
	sf::Packet packet;
	packet << data1 << data2 << 8;

	NetworkPacket networkPacket(SERVER_REJECTS, packet);

	ENetPacket* enetPacket = enet_packet_create(networkPacket.GetBytes(), networkPacket.GetSize(), true);

	NetworkPacket receivedPacket(enetPacket);

	unsigned int data11;
	std::string data22;
	int type;

	receivedPacket.GetPacket() >> data11 >> data22;

	// Create test scene
	Game::addScene(new HelmSceneTest());
	//change the scenes by commenting the other scenes and uncomment the one with the enemysceneTest for the enemies
	//Game::addScene(new EnemySceneTest());

	//Code to add the GalaxyMap to the current scene
	//Game::getCurrentScene()->addComponent(galaxyMap);
	
	
	// Start the main loop
	Game::run();

	return 0;
}