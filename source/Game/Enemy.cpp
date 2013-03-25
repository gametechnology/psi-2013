#include "Enemy.h"


Enemy::Enemy(void)
{
}

Enemy::Enemy(ISceneManager* smgr, IMesh* mesh, 
		vector3df position,
		vector3df rotation,
		unsigned int maxspeed,
		unsigned int agility,
		unsigned int maxacc,
		unsigned int damage,
		unsigned int los,
		unsigned int health) 
{
	setVisual(mesh, smgr);
	setPosition(position);
	setRotation(rotation);
	setMaxSpeed(maxspeed);
	setAgility(agility);
	setMaxAccelaration(maxacc);
	setDamage(damage);
	setLoS(los);
	setHealth(health);


}

void Enemy::pathFinding()
{
	//TODO
}

void Enemy::update()
{
	pathFinding();
}

void Enemy::setState()
{
	//TODO
}
void Enemy::getState()
{
	//TODO
}

void Enemy::setVisual(IMesh* visual, ISceneManager* smgr)
{
	visual_ = visual;
	smgr->addMeshSceneNode(this->visual_);
}

void Enemy::setPath(vector3df destination)
{
	destination_ = destination;
}
void Enemy::setPosition(vector3df position)
{
	position_ = position;
}
void Enemy::setRotation(vector3df rotategoal)
{
	rotation_ = rotategoal;
}
void Enemy::setMaxSpeed(unsigned int maxspeed)
{
	maxspeed_ = maxspeed;
}
void Enemy::setAgility(unsigned int agility)
{
	agility_ = agility;
}
void Enemy::setMaxAccelaration(unsigned int maxacc)
{
	maxaccelaration_ = maxacc;
}
void Enemy::setDamage(unsigned int damage)
{
	damage_ = damage;
}
void Enemy::setLoS(unsigned int los)
{
	lineofsightrange_ = los;
}
void Enemy::setHealth(signed int health)
{
	health_ = health;
}

vector3df Enemy::getPath()
{
	return destination_;
}
vector3df Enemy::getPosition()
{
	return position_;
}
vector3df Enemy::getRotation()
{
	return rotation_;
}
unsigned int Enemy::getMaxSpeed()
{
	return maxspeed_;
}
unsigned int Enemy::getAgility()
{
	return agility_;
}
unsigned int Enemy::getMaxAccelaration()
{
	return maxaccelaration_;
}
unsigned int Enemy::getDamage()
{
	return damage_;
}
unsigned int Enemy::getLoS()
{
	return lineofsightrange_;
}

signed int Enemy::getHealth()
{
	return health_;
}

Enemy::~Enemy(void)
{
}
