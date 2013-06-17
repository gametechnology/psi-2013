#include "Engine\SceneManager.h"

SceneManager::SceneManager() : Component() {
	
}

void SceneManager::init(){
	Component::init();
}

void SceneManager::drawAll() {
	for(unsigned int i = 0; i < nameScenes.size(); i++) {
		if (nameScenes[i].scene->enabled && !nameScenes[i].scene->destroyed)
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
		for(unsigned int i = 0; i< nameScenes.size(); i++){
			if (*nameScenes[i].name == *name){
				nameScenes.erase(nameScenes.begin() + i);
			}
		} 
	}
}

Scene* SceneManager::getLastScene() {
	return nameScenes[nameScenes.size() - 1].scene;
}

//Activates Scene so it update &  be drawed
void SceneManager::activateScene(char* name){
	if (exists(name)) {
		Scene* scene = getScene(name);
		// scene->activate();
		scene->enable();
		scene->addGuiElements();
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
NameScene* SceneManager::getNameScene(char* name){
	if (exists(name)) {
		for(unsigned int i = 0; i< nameScenes.size(); i++){
			if (*nameScenes[i].name == *name) {
				return &nameScenes[i];
			}
		} 
		return NULL;
	}else{
		return NULL;
	}
}

//return the NameScene of a scene, so you'll get the name & scene object
NameScene* SceneManager::getNameScene(Scene* scene) {
	for(unsigned int i = 0; i < nameScenes.size(); i++) {
		if(nameScenes[i].scene == scene) {
			return &nameScenes[i];
		}
	}
	return NULL;
}

//Returns the Scene object
Scene* SceneManager::getScene(char* name){

	NameScene* namesc = getNameScene(name);
	if(namesc != NULL)
	{
		return namesc->scene;
	}else
	{
		return NULL;
	}

}

//Destroys Scene, Deletes the scene properly
bool SceneManager::destroyScene(char* name){
	if (exists(name)) {	
		for(unsigned int i = 0; i < nameScenes.size(); i++){
			//Checks for the right scene
			if (*nameScenes[i].name == *name) {
				if( entity->removeChild(nameScenes[i].scene) ){
					nameScenes.erase(nameScenes.begin() + i);
					return true;
				}else
					return false;
			}
		}
		return false;
	}else{
		return false;
	}
}

bool SceneManager::exists(char* name){
	for(unsigned int i = 0; i<nameScenes.size(); i++){
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
