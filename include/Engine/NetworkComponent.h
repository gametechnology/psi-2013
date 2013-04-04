#ifndef NETWORKCOMPONENT
#define NETWORKCOMPONENT

#include "Component.h"
#include "Composite.h"

#include <list>

#include <enet\enet.h>
#include <string>

class NetworkComponent : public Component
{
private:
	std::list<void*> variables;
public:
	NetworkComponent(Composite* parent);
	~NetworkComponent();
	void registerVar(void* var) { variables.push_back(var); };
};

#endif