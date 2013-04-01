#ifndef HELMTEST_H
#define HELMTEST_H
#include "Engine\Scene.h"
class HelmSceneTest :
	public Scene
{
public:
	HelmSceneTest(void);
	~HelmSceneTest(void);
	virtual void init();
	virtual void update();
	irr::io::path filename;


	//Entity* ship;
	Entity* camera;
	ILightSceneNode* light;
};
#endif