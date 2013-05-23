#ifndef SHIELDCOMPONENT
#define SHIELDCOMPONENT

#include "../../include/Engine/Component.h"
#include "Stations/Station.h"

class ShieldComponent : public Component
{
public:
	ShieldComponent();
	~ShieldComponent();
	void increaseShield(int shield);
	void decreaseShield(int shield);

	//Station information
	const static int maxShield = 100;
	int shield;

};

#endif