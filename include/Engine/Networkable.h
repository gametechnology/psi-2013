#ifndef NETWORKABLE
#define NETWORKABLE

#include "Component.h"
#include "Composite.h"

#include <enet\enet.h>
#include <string>

class Networkable : public Component
{	
	// Event from which received data will be read.
	ENetEvent event;

	// The packet to send as answer.
	ENetPacket *packet;

public:
	/*
	*
	* Initializes ENET and binds an atexit event.
	* Returns prints an error and waits for an input if the initialization fails.
	*
	*/
	Networkable(Composite* parent);

	/*
	*
	* Destroys all the variables held by this class.
	*
	*/
	~Networkable();
};

#endif