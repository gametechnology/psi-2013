#ifndef PSI_GAMEOBJECT
#define PSI_GAMEOBJECT

#include "Composite.h"

class GameObject : public Composite
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void setEnabled(bool enabled);

	virtual void addComponent(Component* component);
	virtual void removeComponent(Component* component);

	virtual void init();

	virtual void handleMessage(unsigned int message, void* data);

	virtual void update();
	virtual void contactResolver(GameObject*);

	irr::core::vector3df* getPosition() { return _position; };
	void setPosition(irr::core::vector3df* position) { _position = position; };

	irr::core::vector3df* getRotation() { return _rotation; };
	void setRotation(irr::core::vector3df* rotation) { _rotation = rotation; };
	
	irr::core::vector3df* getVelocity() { return _velocity; };
	void setVelocity(irr::core::vector3df* velocity) { _velocity = velocity; };

	irr::core::vector3df* getAcceleration() { return _acceleration; };
	void setAcceleration(irr::core::vector3df* acceleration) { _acceleration = acceleration; };

	irr::core::vector3df* getAngularVelocity() { return _angularVelocity; };
	irr::core::vector3df* getAngularAcceleration() { return _angularAcceleration; };

	irr::core::vector3df* getRadius() { return _radius; };
	void setRadius(irr::core::vector3df* radius) { _radius = radius; };
	void setRadius(float radius) { _radius = new irr::core::vector3df(radius, radius, radius); };

	irr::core::vector3df* getForce() { return _force; };
protected:
	float mass;

	irr::core::vector3df* _position;
	irr::core::vector3df* _rotation;
	irr::core::vector3df* _velocity;
	irr::core::vector3df* _acceleration;
	irr::core::vector3df* _angularVelocity;
	irr::core::vector3df* _angularAcceleration;
	irr::core::vector3df* _radius;
	irr::core::vector3df* _force;

	irr::core::vector3df componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity);
};

#endif
