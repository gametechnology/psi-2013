#ifndef PSI_GAMEOBJECT
#define PSI_GAMEOBJECT

#include "Composite.h"

class GameObject : public Composite
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void addComponent(Component* component);
	virtual void removeComponent(Component* component);

	virtual void init();

	virtual void handleMessage(unsigned int message, void* data);

	virtual void update();
	virtual void contactResolver(GameObject*);

	irr::core::vector3df* getPosition() { return _position; };
	irr::core::vector3df* getRotation() { return _rotation; };
	
	irr::core::vector3df* getVelocity() { return _velocity; };
	void setVelocity(irr::core::vector3df* velocity) { _velocity = velocity; };

	irr::core::vector3df* getAcceleration() { return _acceleration; };
	irr::core::vector3df* getAngularVelocity() { return _angularVelocity; };
	irr::core::vector3df* getAngularAcceleration() { return _angularAcceleration; };
	irr::core::vector3df* getRadius() { return _radius; };
	irr::core::vector3df* getForce() { return _force; };
	bool isEnabled() { return _enabled; };
private:
	bool _enabled;

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
