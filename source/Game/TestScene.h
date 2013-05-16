#ifndef PlayScene
#define PlayScene

#include "Engine/Scene.h"
#include "Engine/Entity.h"

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