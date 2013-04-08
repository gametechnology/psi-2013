#ifndef ENEMY_SCENE_TEST_H
#define ENEMY_SCENE_TEST_H

#include "Engine\Scene.h"

class EnemySceneTest :
	public Scene
{
public:
	EnemySceneTest(void);
	~EnemySceneTest(void);
	virtual void init();

	ISceneManager* smgr;
	ICameraSceneNode* camera;
	ILightSceneNode* light;
};

#endif