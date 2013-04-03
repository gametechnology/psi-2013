#ifndef WORMHOLE
#define WORMHOLE

#include "Messages.h"
#include "Engine/Entity.h"

class WormHole : public Entity  {
private:
	unsigned int id;
public:
	WormHole(Composite* parent, unsigned int id, irr::core::vector3df position);
	void handleMessage(unsigned int message, void* data = 0);
	//void update();
	unsigned int getId(){ return this->id; }
	virtual ~WormHole();
};

#endif
