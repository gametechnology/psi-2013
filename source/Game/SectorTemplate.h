#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

/*
* TODO This class is a mess. Refactor this.
* There are too many includes and its intent
* is unclear.
*/ 
#include <Engine/Composite.h>
#include <Engine/BillboardComponent.h>
#include <Engine/Skybox.h>
#include <Engine/Core.h>
#include <vector>

#include "Mist.h"
#include "Messages.h"
#include "EnemyManager.h"
#include "NetworkInterface.h"
#include "EnemyAsteroid.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"

#include "SendAndReceivePackets.h"

class SectorManager;

/*
* This is not a scene, if it is; change the name.
* TODO Document this class, it's a disaster.
*/

class SectorTemplate : public Composite, public INetworkListener  
{
public:
	SectorTemplate(Core*, SectorManager* sectormanager, std::string skyBoxTexture, float boundry, unsigned int amountWormHoles );
	virtual ~SectorTemplate();

	virtual void handleMessage( unsigned int message, void* data = 0) { };
	virtual void update();
	virtual void init();

	void createWormHoles( unsigned int amountOfWormHoles );
	void createEnemies();

	/*
	* TODO This is obviously an obscene hack, just to get access
	* to network packages. Fix this class as soon as possible.
	*/
	virtual void handleNetworkMessage(NetworkPacket packet);
protected:
	Core* _core;
	SectorManager* _sectormanager;

	std::string _skyboxPath;

	std::vector<Enemy*> _enemyList;
	irr::core::vector3df* _playerPosition;
	std::vector<BillboardComponent*> _wormHoles;

	float _boundry;
	Mist* _fog;
};

#endif
