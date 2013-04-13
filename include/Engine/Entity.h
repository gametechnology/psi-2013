#ifndef ENTITY
#define ENTITY

#include "Engine\Composite.h"
#include "Engine\Component.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"

#include "Irrlicht\irrlicht.h"
#include "Irrlicht\vector3d.h"
#include "Irrlicht\irrMath.h"
#include <string>
#include <vector>

using namespace irr;
using namespace core;

class Entity : public Composite {
public:
	Entity();
	virtual ~Entity();

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
