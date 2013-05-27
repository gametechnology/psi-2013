#ifndef SHIP_SCENES
#define SHIP_SCENES

#include <Engine/Scene.h>
#include <Engine/GameObject.h>
#include <Engine/CameraComponent.h>

class ShipScenes :	public Scene
{
public:
	ShipScenes(void);
	~ShipScenes(void);
	void init();

	GameObject* ship;
	CameraComponent* camera;
};

#endif

