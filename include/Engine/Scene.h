#ifndef SCENE
#define SCENE

#include "Entity.h"
#include "Irrlicht\irrlicht.h"

class Scene : public Entity {
public:
	Scene();
	virtual ~Scene();

	void onAdd();

	enum State {
		LOADING,
		PLAYING,
		PAUSED,
		EXITING
	};

	State state;
	irr::scene::ISceneManager* sceneManager;
};

#endif
