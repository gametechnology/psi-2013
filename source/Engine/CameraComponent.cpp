#include <Engine\CameraComponent.h>
#include <Engine/GameObject.h>

using namespace irr;
using namespace irr::scene;
using namespace irr::core;

CameraComponent::CameraComponent(ISceneManager* smgr, CameraType type) : Component("Camera")
{
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	this->smgr = smgr;
	_parent = NULL;
	_type = type;

	cameraNode = NULL;
}

CameraComponent::CameraComponent(ISceneManager* smgr, CameraType type, GameObject* parent) : Component("Camera")
{
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	this->smgr = smgr;
	_parent = parent;
	_type = type;

	cameraNode = NULL;
}

CameraComponent::~CameraComponent()
{
	smgr->addToDeletionQueue(cameraNode);
	smgr = NULL;
}

void CameraComponent::init()
{
	if(_parent != NULL)
		createCamera(_type, _parent->getNode());
	else
		createCamera(_type);
}

void CameraComponent::update()
{
	/*if(_parent != NULL && cameraNode != NULL)
	{
		vector3df offset = vector3df(0);

		matrix4 m;
		
		m.setRotationDegrees(*_parent->getRotation());

		vector3df vrf = vector3df(0, 0, 1);

		m.transformVect(vrf);

		vector3df upv = vector3df(0, 1, 0);

		m.transformVect(upv);

		m.transformVect(offset);
		
		offset += *_parent->getPosition();

		cameraNode->setPosition(offset);
		cameraNode->setUpVector(upv);
		
		offset += vrf;
		
		cameraNode->setTarget(offset);
		cameraNode->updateAbsolutePosition();
	}*/
}

ICameraSceneNode* CameraComponent::getCameraNode()
{
	return cameraNode;
}

void CameraComponent::createCamera(unsigned int type, ISceneNode* parent, f32 rotateSpeed, f32 moveSpeed)
{
	switch(type)
	{
	case(FIRST_PERSON):
		cameraNode = smgr->addCameraSceneNodeFPS(parent, rotateSpeed, moveSpeed, -1, keyMap, 8);
		break;
	case(THIRD_PERSON):
		cameraNode = smgr->addCameraSceneNode(parent);
		break;
	case(MAYA):
		cameraNode = smgr->addCameraSceneNodeMaya(parent);
		break;
	}
}
