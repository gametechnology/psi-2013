#ifndef COMPONENT
#define COMPONENT
#pragma once

#include "Composite.h"

class Entity;
class Scene;
class Game;

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

	virtual void onEnabled();
	virtual void onDisabled();

	virtual void handleMessage(unsigned int message);
};


#endif
