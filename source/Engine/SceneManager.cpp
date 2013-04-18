#include "Engine\SceneManager.h"

SceneManager::SceneManager():Component(){
	//sceneList = new std::vector<Scene*>();
}

void SceneManager::init(){
	//add scenes here
}

void SceneManager::addScene(char* name,Scene* scene){
	if (exists(name)) {
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
			if (&nameScenes[i].name == &name)
			{
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
void SceneManager::destroyScene(char* name){
	if (exists(name)) {
		for(int i = 0; i < nameScenes.size(); i++){
		 delete &nameScenes[i].name;
		 this->entity->removeChild(nameScenes[i].scene);
		 delete &nameScenes[i].scene;
		 delete&nameScenes[i];
		}
	}
}

bool SceneManager::exists(char* name){
	NameScene namesc = getNameScene(name);
	for(int i = 0; i<nameScenes.size(); i++){
		if (&nameScenes[i].name == &name)
			return true;
	}
	return false;
	
}

SceneManager::~SceneManager(){
	for(int i = 0; i< nameScenes.size(); i++){
		delete &nameScenes[i].name;
		// check if deconstructor is called
		this->entity->removeChild(nameScenes[i].scene);
		delete &nameScenes[i].scene;
		delete &nameScenes[i];
	}
}
