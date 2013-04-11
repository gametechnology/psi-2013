#include "Engine\Entity.h"
#include "Engine\Scene.h"
#include "Engine\Game.h"

#ifndef COMPONENT
#define COMPONENT

class Component : public Composite {
public:
	Component();
	virtual ~Component();

	Entity entity;

	Game getGame();
	Scene getScene();

	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void handleMessage(unsigned int message);
};


#endif

