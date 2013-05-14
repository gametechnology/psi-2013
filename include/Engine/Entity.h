#ifndef ENTITY
#define ENTITY

#include "Composite.h"
#include "Component.h"
#include "Transform.h"
#include "Collision.h"

class Game;

class Entity : public Composite {
public:
	Entity();
	virtual ~Entity();

	Game* game;
	Scene* scene;

	Transform* transform;

	Entity* parent;
	std::vector<Component*> components;
	std::vector<Entity*> children;

	void addChild(Entity* child);
	bool removeChild(Entity* child);
	bool removeChild(Entity* child, bool deleteChild);
	void addComponent(Component* component);
	bool removeComponent(Component* component);
	virtual void contactResolverA(Entity* _input);

	virtual void onAdd();
	virtual void init();

	virtual void handleMessage(unsigned int message);
 
	virtual void destroy();
	virtual void update();
	virtual void lateUpdate();
	virtual void draw();
};

#endif
