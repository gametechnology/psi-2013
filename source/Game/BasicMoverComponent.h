#ifndef BASICMOVERCOMPONENT
#define BASICMOVERCOMPONENT

#include "Engine/Component.h"
#include "Engine/Entity.h"

class BasicMoverComponent : public Component  {
public:
	float mass;
	float thrust;

	BasicMoverComponent();
	virtual ~BasicMoverComponent();
	virtual void update();
private:

};

#endif