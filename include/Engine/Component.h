#ifndef COMPONENT
#define COMPONENT

#include "Composite.h"

class Scene;
class Game;
class Entity;

class Component : public Composite {
public:
	Component();
	virtual ~Component();

	Entity* entity;

	Game* getGame();
	Scene* getScene();

	virtual void onAdd();
	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void handleMessage(unsigned int message);
};


#endif

