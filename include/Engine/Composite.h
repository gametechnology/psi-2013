#ifndef PSI_COMPOSITE
#define PSI_COMPOSITE

#include "Component.h"

#include <list>
#include <iostream>

class Composite : public Component 
{
public:
	virtual ~Composite()
	{
		for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
		{
			delete *i;
		}

		Component::~Component();
	}

	virtual void setEnabled(bool enabled)
	{
		for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
		{
			(*i)->setEnabled(enabled);
		}

		Component::setEnabled(enabled);
	}

	virtual void init()
	{
		for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
		{
			if((*i)->isEnabled())
				(*i)->init();
		}

		Component::init();
	}

	virtual void update()
	{
		for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
		{
			if((*i)->isEnabled())
			{
				(*i)->update();
			}
		}

		Component::update();
	}

	virtual void draw()
	{
		for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
		{
			if((*i)->isEnabled())
				(*i)->draw();
		}

		Component::draw();
	}

	virtual void handleMessage(unsigned int message, void* data)
	{
		std::list<Component*>::iterator i;
		for (i = components.begin(); i != components.end(); ++i)
		{
			if((*i)->isEnabled())
				(*i)->handleMessage(message, data);
		}
		delete *i;

		Component::handleMessage(message, data);
	}

	virtual void addComponent(Component* component) 
	{
		components.push_back(component);
	}

	virtual void removeComponent(Component* component)
	{
		components.remove(component);
	}
protected:
	std::list<Component*> components;

	Composite(const char* name) : Component(name) { };
};

#endif
