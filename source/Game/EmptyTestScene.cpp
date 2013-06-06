#include "EmptyTestScene.h"
#include <iostream>
#include <stdlib.h>

EmptyTestScene::EmptyTestScene(void){


}

EmptyTestScene::~EmptyTestScene(void) {


}

void EmptyTestScene::onAdd(){
	a = 0;
	//b = 25;

	//hud = new HudComposite( &a, &b, rect<s32>(10,240,110,240 + 32));
	//addChild(hud);
	addChild(ship);
}

void EmptyTestScene::init(){
	

	Entity::init();
	ship = new Ship(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));
}

void EmptyTestScene::update(){
	/*
	if(game->input->isKeyboardButtonDown(KEY_KEY_W)){
		a -= 1;
	}
	*/
	if(game->input->isKeyboardButtonDown(KEY_KEY_S)){
		a = rand() % 100;
		std::cout << "Give " << a << " of damage to the ship" << endl;
		ship->shipHealthComponent->assignDamage(a);
	}
	
	
}