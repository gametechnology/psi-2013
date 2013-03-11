#include "Composite.h"

Composite::Composite():Component(NULL)
{
}

Composite::Composite(Composite* parent):Component(parent)
{
}


Composite::~Composite()
{
}

void Composite::Init()
{
}

void Composite::HandleMessage(unsigned int message, void* data)
{
	for (list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->HandleMessage(message, data);
	}
}

void Composite::Update()
{
	for (list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->Update();
	}
}

void Composite::AddComponent(Component* component)
{
	components.push_back(component);
}

void Composite::RemoveComponent(Component* component)
{
	components.remove(component);
}

