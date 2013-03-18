#include "Scene.h"
#include "Entity.h"

#ifndef PlayScene
#define PlayScene

class HelmScene : public Scene 
{
public:
	HelmScene(void);
	~HelmScene(void);
	
	void init();
	virtual void update();
	void createRandomPlanets(int amountOfPlanets);

	static IrrlichtDevice* device;

	u32 then;
	KeyEventReceiver rv;
	Entity* HelmModel; 
	Entity* Planets;
	Entity* camera;
};

#endif