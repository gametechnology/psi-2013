#include "Composite.h"
#include "Entity.h"
#include <Irrlicht\irrlicht.h>


#ifndef SCENE
#define SCENE

using namespace core;
using namespace scene;

class Scene : public Composite
{
public:
	Scene();
	~Scene(void);

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
