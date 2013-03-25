#include "Component.h"
#include <list>

#ifndef COMPOSITE
#define COMPOSITE

class Composite : public Component
{
public:
	Composite(Composite* parent);
	virtual ~Composite();

	virtual void update();
	virtual void draw();
	virtual void handleMessage(unsigned int message, void* data);

	virtual void addComponent(Component* component);
	virtual void removeComponent(Component* component);
protected:
	std::list<Component*> components;
};

#endif