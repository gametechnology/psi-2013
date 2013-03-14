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

void Composite::init()
{
}

void Composite::handleMessage(unsigned int message, void* data)
{
	for (list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->handleMessage(message, data);
	}
}

void Composite::update()
{
	for (list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->update();
	}
}

void Composite::addComponent(Component* component)
{
	components.push_back(component);
}

void Composite::removeComponent(Component* component)
{
	components.remove(component);
}

