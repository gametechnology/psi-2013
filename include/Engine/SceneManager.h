#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "Component.h"

class SceneManager : public Component {
public:
	SceneManager();
	~SceneManager();

	void drawAll();
};

#endif