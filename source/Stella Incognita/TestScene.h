#include "Scene.h"
#include "Entity.h"

#ifndef PlayScene
#define PlayScene

class TestScene : public Scene
{
public:
	TestScene(void);
	~TestScene(void);
	void init();

	Entity* testModel;
	Entity* camera;
};

#endif