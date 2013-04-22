#include "EmptyTestScene.h"
#include <iostream>

EmptyTestScene::EmptyTestScene(void){


}

EmptyTestScene::~EmptyTestScene(void) {


}

void EmptyTestScene::init(){
	a = 100;
	
	
	healthBar = new HealthBar(this, vector2df(300, 300), &a, vector2df(28, 8), 2);
	addComponent(healthBar);
}

void EmptyTestScene::update(){
	if(Game::input->isKeyboardButtonDown(KEY_KEY_W)){
		a -= 1;
	}
}