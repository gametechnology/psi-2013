#include "Laser.h"
#include "Stations/DefenceStation.h"
#include "EnemyDrone.h"

using namespace irr;
using namespace irr::core;

int Laser::newLaserId = 0;

Laser::Laser() : Enemy()
{	
	this->_damage = 10;
}

Laser::Laser(irr::scene::ISceneManager* smgr) : Enemy()
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

	Enemy::init();
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
	_position->dotProduct(_direction);
	_position->operator+=(_direction);
	_position->operator+=(_direction);
	_position->operator+=(_direction);
	_position->operator+=(_direction);
	*_rotation = _direction;

	*_velocity = _direction * speed;

	*_velocity = _direction * speed;
}

int Laser::getId()
{
	return _id;
}

void Laser::setId(int id)
{
	// FFS STOP ALL THE this->
	_id = id;
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

/*void Laser::contactResolverA(Enemy* input)
{
	Enemy* tempEnemy = dynamic_cast<Enemy*>(input);
	tempEnemy->setHealth(tempEnemy->getHealth() - this->_damage);
	setEnabled(false);
}*/

void Laser::contactResolverA(DefenceStation* input)
{
	input->Damage();
	std::printf("HIT on Defence station! \n");
	setEnabled(false);
}