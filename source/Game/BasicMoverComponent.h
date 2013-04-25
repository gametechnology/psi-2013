#ifndef BASICMOVERCOMPONENT
#define BASICMOVERCOMPONENT

#include "Engine/Component.h"
#include "Engine/Entity.h"
#include "NetworkInterface.h"

class BasicMoverComponent : public Component, public INetworkListener  {
public:
	float mass;
	float thrust;
	Entity* entityParent;

	BasicMoverComponent(Entity* parent);
	virtual ~BasicMoverComponent();
	virtual void update();
	void HandleNetworkMessage(NetworkPacket packet);
private:

};

#endif