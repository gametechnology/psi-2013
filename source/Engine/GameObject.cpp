#include <Engine/GameObject.h>

GameObject::GameObject() : Composite("GameObject")
{
	mass = 1;

	_position = new irr::core::vector3df();
	_rotation = new irr::core::vector3df();
	_velocity = new irr::core::vector3df();
	_acceleration = new irr::core::vector3df();
	_angularVelocity = new irr::core::vector3df();
	_angularAcceleration = new irr::core::vector3df();
	_force = new irr::core::vector3df();
	_radius = new irr::core::vector3df(1,1,1);
}

GameObject::~GameObject()
{
	delete _position;
	delete _rotation;
	delete _velocity;
	delete _acceleration;
	delete _angularVelocity;
	delete _angularAcceleration;
	delete _radius;
}

void GameObject::addComponent(Component* component)
{
	Composite::addComponent(component);
}

void GameObject::removeComponent(Component* component)
{
	Composite::removeComponent(component);
}

void GameObject::update()
{
	*_angularVelocity += *_angularAcceleration;
	*_rotation += *_angularVelocity;

	*_acceleration = (1 / this->mass)**(this->_force);
	*_velocity += *_acceleration;
	*_position += *_velocity;

	Component::update();
}

void GameObject::init()
{
}

void GameObject::handleMessage(unsigned int message, void* data)
{
}

void GameObject::contactResolver(GameObject* otherObject)
{
	float deltamass = (_radius->X / otherObject->getRadius()->X);

	irr::core::vector3df deltavelocity = *_velocity - *otherObject->getVelocity();
	irr::core::vector3df componentThisToBal = componentOnto(
		*otherObject->getPosition() - *_position,
		deltavelocity);
	irr::core::vector3df componentNormalToBal = deltavelocity - componentThisToBal;
	irr::core::vector3df thisMassComponent = componentThisToBal * (((deltamass- 1) / (deltamass + 1)));
	irr::core::vector3df balMassComponent = componentThisToBal * ((2 * deltamass / (deltamass + 1)));

	_velocity = &(componentNormalToBal + thisMassComponent + *otherObject->getVelocity());

	otherObject->setVelocity(&(balMassComponent + *otherObject->getVelocity()));
	_radius->X = (_radius->X*2 - _position->getDistanceFrom(*otherObject->getPosition()));
	otherObject->getRadius()->X = (_radius->X);
}

irr::core::vector3df GameObject::componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity)
{
	return input * (deltavelocity.dotProduct(input) / input.getLengthSQ());
}