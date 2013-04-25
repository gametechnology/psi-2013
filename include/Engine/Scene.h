#ifndef SCENE
#define SCENE

#include "Entity.h"
#include "Irrlicht\irrlicht.h"

class Scene : public Entity {
public:
	Scene();
	virtual ~Scene();

	void onAdd();

	irr::scene::ISceneManager* getIrrlichtSceneManager();

	enum State {
		LOADING,
		PLAYING,
		PAUSED,
		EXITING
	};

	State state;
};

#endif
