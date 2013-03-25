#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

#include "Engine/Entity.h"
class SectorTemplate : public Entity  {
public:

	SectorTemplate(Composite* parent, const io::path & skyBoxTexture, float boundry);
	void SectorTemplate::handleMessage(unsigned int message, void* data = 0);
	void SectorTemplate::update();
	void SectorTemplate::init();
	virtual ~SectorTemplate();
private:
	float _boundry;
	vector3df *_playerPosition;
	Entity *_player;
	Entity *_skybox;
};

#endif
