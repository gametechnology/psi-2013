#include "EmptyTestScene.h"
#include <iostream>

EmptyTestScene::EmptyTestScene(void){


}

EmptyTestScene::~EmptyTestScene(void) {


}

void EmptyTestScene::onAdd(){
	a = 100;
	b = 25;

	hud = new HudComposite( &a, &b);
	addChild(hud);
}

void EmptyTestScene::init(){
	

	Entity::init();
}

void EmptyTestScene::update(){
	if(game->input->isKeyboardButtonDown(KEY_KEY_W)){
		a -= 1;
	}
	if(game->input->isKeyboardButtonDown(KEY_KEY_S)){
		a += 1;
	}
}