#ifndef NETWORKABLE
#define NETWORKABLE

#include "Component.h"
#include "Composite.h"

#include <enet\enet.h>
#include <string>

class Networkable : public Component
{	
public:
	Networkable(Composite* parent);
	~Networkable();
	void registerVar(void* var);
};

#endif