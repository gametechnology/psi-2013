#include "Composite.h"
#include "Entity.h"
#include "irrlicht.h"


#ifndef SCENE
#define SCENE

using namespace std;
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
		EXIT
	};

	State state;
	ISceneManager* smgr;
};

#endif
