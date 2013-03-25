#include "Engine\Composite.h"

Composite::Composite(Composite* parent):Component(parent)
{
}


Composite::~Composite()
{
	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		delete (*i);
	}
	components.clear();
}

void Composite::handleMessage(unsigned int message, void* data)
{
	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->handleMessage(message, data);
	}
}

void Composite::update()
{
	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->update();
	}
}

void Composite::draw()
{
	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->draw();
	}
}

void Composite::addComponent(Component* component)
{
	components.push_back(component);
}

void Composite::removeComponent(Component* component)
{
	components.remove(component);
	delete component;
}

