#include "Engine\SceneManager.h"

SceneManager::SceneManager(){
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

void SceneManager::activateScene(char* name){
	if (exists(name)) {
		Scene* scene = getScene(name);
		// scene->activate();
	}
}

void SceneManager::deactivateScene(char* name){
	if (exists(name)) {
		Scene* scene = getScene(name);
		//scene->deactivate();
	}
}

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

Scene* SceneManager::getScene(char* name){

	NameScene namesc = getNameScene(name);
	return namesc.scene;

}

void SceneManager::destroyScene(char* name){
	if (exists(name)) {
		for(int i = 0; i < nameScenes.size(); i++){
		 delete &nameScenes[i].name;
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
		delete &nameScenes[i].scene;
		delete &nameScenes[i];
	}
}
