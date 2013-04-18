#include <Engine\Component.h>
#include <Engine\Composite.h>

Component::Component(Composite* parent)
{
	this->parent = parent;
}

Component::~Component()
{
}