#ifndef BASICMOVERCOMPONENT
#define BASICMOVERCOMPONENT

#include "Engine/Component.h"
#include "Engine/Entity.h"
#include "NetworkInterface.h"

class BasicMoverComponent : public Component, public INetworkListener   {
public:
	float mass;
	float thrust;

	BasicMoverComponent();
	virtual ~BasicMoverComponent();
	virtual void update();
	void HandleNetworkMessage(NetworkPacket packet);
protected:
	void move(Entity *entity, irr::core::vector3df vel);
	void rotate(Entity *entity, irr::core::vector3df rot);
	void turn(Entity *entity, irr::f32 rot);
	void pitch(Entity *entity, irr::f32 rot);
	void roll(Entity *entity, irr::f32 rot);
};

#endif