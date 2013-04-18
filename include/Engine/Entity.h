#ifndef ENTITY
#define ENTITY
#pragma once

#include "Composite.h"
#include "Component.h"

class Game;

class Entity : public Composite {
public:
	Entity();
	~Entity();

	Game* game;
	Scene* scene;

	Entity* parent;
	std::vector<Component*> components;
	std::vector<Entity*> children;

	virtual void addChild(Entity* child);
	virtual void removeChild(Entity* child);
	virtual void addComponent(Component* component);
	virtual void removeComponent(Component* component);

	virtual void onAdd();
	virtual void init();

	virtual void update();
	virtual void lateUpdate();
};

#endif
