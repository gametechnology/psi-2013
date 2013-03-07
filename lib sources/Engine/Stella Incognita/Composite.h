#include "Component.h"
#include <list>

#ifndef COMPOSITE
#define COMPOSITE

using namespace std;

class Composite : Component
{
public:
	Composite();
	Composite(Composite* parent);
	~Composite();

	list<Component> components;
	virtual void AddComponent(Component component);
	virtual void RemoveComponent(Component component);
	virtual void Update();
};

#endif

