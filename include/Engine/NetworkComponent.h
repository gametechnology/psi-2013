#ifndef NETWORKCOMPONENT
#define NETWORKCOMPONENT

#include "Component.h"
#include "Composite.h"
#include "Networkable.h"

#include <list>

#include <enet\enet.h>
#include <string>

class NetworkComponent : public Component
{
private:
	std::list<Component*> components;
	std::list<int*> integers;
	std::list<float*> floats;
public:
	NetworkComponent();
	~NetworkComponent();

	void update();

	void registerVar(Component* var) { components.push_back(var); };
	void registerVar(int* var) { integers.push_back(var); };
	void registerVar(float* var) { floats.push_back(var); };
};

#endif