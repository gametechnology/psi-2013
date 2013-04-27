#include "Engine\SceneManager.h"

SceneManager::SceneManager() : Component() {
	
}

void SceneManager::init(){
	Component::init();
}

void SceneManager::drawAll() {
	for(int i = 0; i < nameScenes.size(); i++) {
		if (nameScenes[i].scene->enabled)
			nameScenes[i].scene->getIrrlichtSceneManager()->drawAll();
	}
}

void SceneManager::addScene(char* name,Scene* scene){
	if (!exists(name)) {
		NameScene namescene;
		namescene.name = name;
		namescene.scene = scene;
		nameScenes.push_back(namescene);
		this->entity->addChild(scene);
	}
}

void SceneManager::removeScene(char* name) {
	if (exists(name)) {
		for(int i = 0; i< nameScenes.size(); i++){
			if (&nameScenes[i].name == &name)
			{
				nameScenes.erase(nameScenes.begin() + i);
			}
		} 
	}
}

//Activates Scene so it update &  be drawed
void SceneManager::activateScene(char* name){
	if (exists(name)) {
		Scene* scene = getScene(name);
		// scene->activate();
		scene->enable();
	}
}

//Deactivates Scene so it won't update & won't be drawed
void SceneManager::deactivateScene(char* name){
	if (exists(name)) {
		Scene* scene = getScene(name);
		//scene->deactivate();
		scene->disable();
	}
}

//Returns The NameScene of a scene, So you'll can get the name & scene object
NameScene SceneManager::getNameScene(char* name){
	if (exists(name)) {
		for(int i = 0; i< nameScenes.size(); i++){
			if (&nameScenes[i].name == &name) {
				return nameScenes[i];
			}
		} 
	}
}
//Returns the Scene object
Scene* SceneManager::getScene(char* name){

	NameScene namesc = getNameScene(name);
	return namesc.scene;

}

//Destroys Scene, Deletes the scene properly
bool SceneManager::destroyScene(char* name){
	if (exists(name)) {		//exists(name)
		for(int i = 0; i < nameScenes.size(); i++){
			//Checks for the right scene
			if (&nameScenes[i].name == &name) {
				// delete nameScenes[i].name;
				// nameScenes[i].scene->destroy();
				entity->removeChild(nameScenes[i].scene);
				nameScenes.erase(nameScenes.begin() + i);
				return true;
				// delete nameScenes[i].scene;
				// delete &nameScenes[i];
			}
		}
	}else
		return false;
}

bool SceneManager::exists(char* name){
	//NameScene namesc = getNameScene(name);
	printf("[SceneManager]Size: %i",nameScenes.size());
	for(int i = 0; i<nameScenes.size(); i++){
		if (*nameScenes[i].name == *name)
			return true;
	}
	return false;
	
}

SceneManager::~SceneManager(){
	/*for(int i = 0; i< nameScenes.size(); i++){
		delete &nameScenes[i].name;
		// check if deconstructor is called
		this->entity->removeChild(nameScenes[i].scene);
		delete &nameScenes[i].scene;
		delete &nameScenes[i];
	}*/
}
