#ifndef WORMHOLE
#define WORMHOLE

#include "Messages.h"
#include "Engine/BillBoardNode.h"

class WormHole : public BillBoardNode  {
private:
	unsigned int id;
	//irr::scene::IBillboardSceneNode* _wormhole;
public:
	WormHole( unsigned int id );
	virtual ~WormHole();

	void handleMessage(unsigned int message, void* data = 0);
	
	virtual void onAdd();
	//virtual void update();

	unsigned int getId(){ return this->id; }
};

#endif
