#ifndef NETWORKCOMPONENT
#define NETWORKCOMPONENT

#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Irrlicht\irrlicht.h"

#include <list>
#include <Irrlicht\irrlicht.h>
#include <Enet\enet.h>
#include <string>

class NetworkComponent : public Component {
private:
	std::list<Component*> components;
	std::list<irr::core::vector3df*> vectors;
	std::list<int*> integers;
	std::list<float*> floats;
public:
	NetworkComponent();
	~NetworkComponent();

	void update();

	void registerVar(Component* var) { components.push_back(var); };
	void registerVar(irr::core::vector3df* var) { vectors.push_back(var); };
	void registerVar(int* var) { integers.push_back(var); };
	void registerVar(float* var) { floats.push_back(var); };
};

#endif