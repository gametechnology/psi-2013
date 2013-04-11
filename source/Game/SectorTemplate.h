#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

#include "Engine/Scene.h"
#include "SectorManager.h"
#include "WormHole.h"
#include "Mist.h"
#include "Messages.h"
#include "Engine/Game.h"
#include "EnemyManager.h"
#include <vector>

class SectorManager;
class SectorTemplate : public Scene  {
protected:
	std::vector<WormHole*> _wormHoles;
	float _boundry;
	WormHole* wormHole;
	vector3df* _playerPosition;
	// Camera Placeholder instead of player
	irr::scene::ICameraSceneNode *_camera;
	Entity* _player;
	Entity* _skybox;
	Mist* _fog;
public:
	SectorManager* _sectormanager;
	SectorTemplate(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles );
	void handleMessage( unsigned int message, void* data = 0 );
	virtual void update();
	void init();
	void createWormHoles( unsigned int amountOfWormHoles );
	virtual ~SectorTemplate();

private:
	EnemyManager* _enemyManager;
};

#endif
