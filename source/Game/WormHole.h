#ifndef WORMHOLE
#define WORMHOLE

#include "Messages.h"
#include <Engine/BillboardComponent.h>

/* 
* TODO Consider using the BillboardComponent
* directly instead of extending it. See the
* engine documentation.
*/

class WormHole : public BillboardComponent  
{
public:
	WormHole( unsigned int id );
	virtual ~WormHole();

	void handleMessage(unsigned int message, void* data = 0);

	virtual void init();

	unsigned int getId(){ return this->id; }
private:
	unsigned int id;
};

#endif
