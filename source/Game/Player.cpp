#include "Player.h"
#include "Messages.h"
#include <iostream>

Player::Player(Composite* parent) : Entity(parent)
{
	createNode("../assets/sydney.md2");
	i = 0;
	v3f = vector3df(0,0,0);
	networker = new NetworkComponent();
	addComponent(networker);
	networker->registerVar(&i);
	networker->registerVar(&v3f);
}

void Player::update() {
	Composite::update();
	std::cout<<i<<std::endl;
	std::cout<<"vectorx="<<v3f.X<<"\n";
}

void Player::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case DAMAGE: /* Do something */;
	}
	delete data;
}

Player::~Player()
{
	Entity::~Entity();
}
