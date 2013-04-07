#ifndef WORMHOLE
#define WORMHOLE

#include "Messages.h"
#include "Engine/Entity.h"

class WormHole : public Entity  {
private:
	unsigned int id;
	irr::scene::IBillboardSceneNode* _wormhole;
public:
	WormHole(Composite* parent, unsigned int id, irr::core::vector3df position);
	void handleMessage(unsigned int message, void* data = 0);
	void setPosition(irr::core::vector3df &newPos);
	virtual void update();
	unsigned int getId(){ return this->id; }
	virtual ~WormHole();
};

#endif
