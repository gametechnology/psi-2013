#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

#include "Engine/Entity.h"
#include "WormHole.h"
#include <vector>
class SectorTemplate : public Entity  {
public:
	SectorTemplate( Composite* parent, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles );
	void handleMessage( unsigned int message, void* data = 0 );
	void update();
	void init();
	void createWormHoles( unsigned int amountOfWormHoles );
	virtual ~SectorTemplate();

private:
	std::vector<WormHole*> _wormHoles;
	float _boundry;
	WormHole* wormHole;
	vector3df *_playerPosition;
	Entity *_player;
	Entity *_skybox;
};

#endif
