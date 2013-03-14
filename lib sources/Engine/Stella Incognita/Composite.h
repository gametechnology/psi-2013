#include "Component.h"
#include <list>

#ifndef COMPOSITE
#define COMPOSITE

using namespace std;

class Composite : public Component
{
public:
	Composite();
	Composite(Composite* parent);
	~Composite();

	list<Component*> components;

	virtual void init() { };
	virtual void handleMessage(unsigned int message, void* data);
	virtual void update();

	virtual void addComponent(Component* component);
	virtual void removeComponent(Component* component);
};

#endif