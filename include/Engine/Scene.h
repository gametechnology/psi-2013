#ifndef SCENE
#define SCENE

#include "Irrlicht\irrlicht.h"
#include "Engine\Entity.h"

class Scene : public Entity {
public:
	Scene();
	~Scene();

	enum State{
		LOADING,
		PLAYING,
		PAUSED,
		EXITING
	};

	State state;
	ISceneManager* sceneManager;
};

#endif
