#ifndef SHIELDCOMPONENT
#define SHIELDCOMPONENT

#include <Engine/Component.h>

#include "Messages.h"

class Station;

class ShieldComponent : public Component
{
public:
	ShieldComponent();
	~ShieldComponent();
	void increaseShield(int shield);
	void decreaseShield(int shield);
	void handleMessage(unsigned int message, void* data);

	//Station information
	const static int maxShield = 100;
	int shield;

};

#endif