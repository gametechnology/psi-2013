/*
	Example entity for loading a model
*/

#ifndef SECTOR_TEMPLATE
#define SECTOR_TEMPLATE

#include "Engine/Entity.h"
class SectorTemplate : public Entity  {
public:

	SectorTemplate(Composite* parent, Entity player, const io::path & skyBoxTexture, float boundry);
	void SectorTemplate::handleMessage(unsigned int message, void* data = 0);
	void SectorTemplate::update();
	virtual ~SectorTemplate();
private:
	vector3df *_boundry;
	vector3df *_playerPosition;
	Entity *_player;
};

#endif
