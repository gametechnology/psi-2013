#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

#include "Engine/Entity.h"
class AstroidSector : public SectorTemplate  {
public:

	AstroidSector(Composite* parent, const io::path & skyBoxTexture, float boundry);
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
