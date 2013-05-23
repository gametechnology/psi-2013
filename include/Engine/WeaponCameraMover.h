#ifndef WEAPONCAMERAMOVER
#define WEAPONCAMERAMOVER

#include "Engine/Component.h"
#include "Engine/WeaponCamera.h"
//#include "Engine/InputManager.h"

class WeaponCameraMover : public Component
{
public:
	WeaponCameraMover(void);
	virtual ~WeaponCameraMover(void);

	virtual void init();
	virtual void update();

	virtual void draw(){};
	virtual void handleMessage(unsigned int message) {};
private:
	WeaponCamera* weaponCamera;
	//InputManager* input;

	float yawChange;
	float rollChange;
	float pitchChange;
};
#endif