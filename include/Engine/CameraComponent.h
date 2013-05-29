#ifndef PSI_CAMERA
#define PSI_CAMERA

#include "Component.h"

class CameraComponent : public Component
{
public:
	enum CameraType {
		THIRD_PERSON,
		FIRST_PERSON,
		MAYA
	};

	CameraComponent(irr::scene::ISceneManager*, CameraType type);
	~CameraComponent();

	virtual void handleMessage(unsigned int, void* data = 0) { };

	irr::scene::ICameraSceneNode* getCameraNode();
private:
	irr::SKeyMap keyMap[8];
	irr::scene::ISceneManager* smgr;
	irr::scene::ICameraSceneNode* cameraNode;

	void createCamera(CameraType type, irr::scene::ISceneNode* parent = 0, irr::f32 rotateSpeed = 50.0f, irr::f32 moveSpeed = 0.15f);
};


#endif