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

	virtual void Init();
	virtual void HandleMessage(unsigned int message, void* data);
	virtual void Update();

	virtual void AddComponent(Component* component);
	virtual void RemoveComponent(Component* component);
};

#endif