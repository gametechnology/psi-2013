#ifndef SECTOR_ASTROID
#define SECTOR_ASTROID

//#include "Engine/Entity.h"
#include "SectorTemplate.h"
#include "Engine/Game.h"

class AstroidSector : public SectorTemplate  {
public:

	AstroidSector(Composite* parent, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void AstroidSector::handleMessage(unsigned int message, void* data = 0);
	void AstroidSector::update();
	void AstroidSector::init();
	virtual ~AstroidSector();
private:
	float _boundry;
	vector3df *_playerPosition;
	Entity *_player;
	Entity *_skybox;
};

#endif
