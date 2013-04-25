#include "EmptyTestScene.h"
#include <iostream>

EmptyTestScene::EmptyTestScene(void){


}

EmptyTestScene::~EmptyTestScene(void) {


}

void EmptyTestScene::init(){
	a = 100;
	b = 25;
	
	hud = new HudComposite(this, &a, &b);
	addComponent(hud);
}

void EmptyTestScene::update(){
	if(Game::input->isKeyboardButtonDown(KEY_KEY_W)){
		a -= 1;
	}
	if(Game::input->isKeyboardButtonDown(KEY_KEY_S)){
		a += 1;
	}
}