#ifndef ET_SCENE
#define ET_SCENE

#include "Irrlicht/irrlicht.h"
#include "Engine/Game.h"
#include "Engine/Composite.h"
#include "Engine/Component.h"
#include "../../include/Engine/Scene.h"
#include "HealthBar.h"

class EmptyTestScene : public Scene
{

public:
	EmptyTestScene(void);
	~EmptyTestScene(void);
	void init();
	HealthBar* healthBar;
	void update();
	int a;


};

#endif