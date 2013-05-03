#ifndef ET_SCENE
#define ET_SCENE

#include "Irrlicht/irrlicht.h"
#include "Engine/Game.h"
#include "Engine/Composite.h"
#include "Engine/Component.h"
#include "../../include/Engine/Scene.h"
#include "HudComposite.h"

class EmptyTestScene : public Scene
{

public:
	EmptyTestScene(void);
	~EmptyTestScene(void);

	virtual void onAdd();
	virtual void init();

	HudComposite* hud;
	void update();
	int a;
	int b;


};

#endif