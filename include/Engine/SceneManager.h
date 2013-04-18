#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include <vector>
#include <Engine\Scene.h>
#include <stdlib.h>

typedef struct {
	char* name;
	Scene* scene;
} NameScene;

class SceneManager
{
	protected:
	std::vector<NameScene> nameScenes;

public:
	SceneManager();
	~SceneManager(void);
	void init();
	void addScene(char* name,Scene* scene);
	void removeScene(char* name);
	void activateScene(char* name);
	void deactivateScene(char* name);
	NameScene getNameScene(char* name);
	Scene* getScene(char* name);
	void destroyScene(char* name);
	bool exists(char* name);
};



#endif