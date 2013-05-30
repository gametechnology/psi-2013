#include "Laser.h"
#include "Stations/DefenceStation.h"

using namespace irr;
using namespace irr::core;

int Laser::newLaserId = 0;

Laser::Laser()
{
}

Laser::Laser(irr::scene::ISceneManager* smgr) : GameObject()
{
	_currentLife = 0;
	_timeofLife = 250;
	_damage = 1;
	_hasAnIrrlichtNode = false;
	_id = newLaserId++;
	_smgr = smgr;
	setEnabled(false);
}

void Laser::init() 
{
	_mesh = new MeshComponent(_smgr);
	addComponent(_mesh);
	_mesh->createMeshNode("../assets/Models/laser.3ds");

	GameObject::init();
}

Laser::~Laser() 
{

}

void Laser::fire(vector3df* position, vector3df* rotation, vector3df target, f32 speed)
{
	setEnabled(true);
	_position = position;
	_rotation = rotation;
	_rotation += 90;
	
	_direction = target - *_position;
	_direction.normalize();

	*_velocity = _direction * speed;
}

int Laser::getId()
{
	return this->_id;
}

void Laser::setId(int id)
{
	this->_id = id;
}

void Laser::update()
{
	GameObject::update();
}

void Laser::setScene(Scene& scene)
{
	_scene = &scene;
}

Scene* Laser::getScene()
{
	return _scene;
}

void Laser::contactResolverA(Enemy* input)
{
	input->setHealth(input->getHealth() - this->_damage);
	std::printf("HIT on Enemy!");
	setEnabled(false);
}

void Laser::contactResolverA(DefenceStation* input)
{
	input->Damage();
	std::printf("HIT on Defence station!");
	setEnabled(false);
}