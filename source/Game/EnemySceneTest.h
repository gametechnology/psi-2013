#ifndef ENEMY_SCENE_TEST_H
#define ENEMY_SCENE_TEST_H

#include "Engine\Scene.h"
#include "Irrlicht\ICameraSceneNode.h"
#include "Irrlicht\ILightSceneNode.h"

class EnemySceneTest :
	public Scene
{
public:
	EnemySceneTest(void);
	~EnemySceneTest(void);
	virtual void init();

	irr::scene::ICameraSceneNode* camera;
	irr::scene::ILightSceneNode* light;
};

#endif