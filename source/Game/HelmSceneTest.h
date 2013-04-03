#ifndef HELMTEST_H
#define HELMTEST_H
#include "Engine\Scene.h"
#include "HelmStation.h"
#include "Skybox.h"
#include "Enemy.h"

class HelmSceneTest :
	public Scene
{
public:
	HelmSceneTest(void);
	~HelmSceneTest(void);
	virtual void init();
	virtual void update();
	irr::io::path filename;

	Enemy* drone1;
	ISceneManager* smgr;
	ICameraSceneNode* camera;
	ILightSceneNode* light;
};
#endif