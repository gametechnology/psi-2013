#include "Component.h"
#include "Composite.h"

Component::Component(Composite* parent)
{
	this->parent = parent;
}

Component::~Component()
{
}