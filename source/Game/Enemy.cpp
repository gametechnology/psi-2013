#include "Enemy.h"
#include <string>

Enemy::Enemy(void): Entity(parent)
{
}

Enemy::Enemy(ISceneManager* smgr, IMesh* mesh, 
		vector3df position,
		vector3df rotation,
		unsigned int maxspeed,
		unsigned int agility,
		vector3df acc,
		unsigned int damage,
		unsigned int los,
		unsigned int health): Entity(parent)
{
	setVisual(mesh, smgr);
	setPosition(position);
	setRotation(rotation);
	setMaxSpeed(maxspeed);
	setAgility(agility);
	setAccelaration(acc);
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
	applySpeed();
	Entity::update();
}

bool isWithinLoS(/*playership class*/)
{
	return false;
}

void Enemy::applySpeed()
{
	if (velocity.getLength() > maxspeed_)
	{
		vector3df cappedvel = velocity.normalize();
		cappedvel *= maxspeed_;
		velocity = cappedvel;
	}
}

void Enemy::steeRing()
{

}

void Enemy::contactResolverB()
{
	velocity *= -1;
}

void Enemy::contactResolverA(Enemy input)
{
	
}

void Enemy::contactGenerator(Enemy* input)
{
	float distance = position.getDistanceFrom(input->getPosition());
	float radii = input->getRadius() + radius_;
	if (distance < radii)
	{
		contactResolverB();
	}
}

void Enemy::setVisual(IMesh* visual, ISceneManager* smgr)
{
	visual_ = visual;
	smgr->addMeshSceneNode(this->visual_);
}

void Enemy::setVisualWithPath(std::string path)
{
	this->createNode(path);
}

void Enemy::setVelocity(vector3df input)
{
	velocity = input;
}
void Enemy::setPath(vector3df destination)
{
	destination_ = destination;
}
void Enemy::setPosition(vector3df pos)
{
	position = pos;
}
void Enemy::setRotation(vector3df rotategoal)
{
	orientation = rotategoal;
}
void Enemy::setMaxSpeed(unsigned int maxspeed)
{
	maxspeed_ = maxspeed;
}
void Enemy::setAgility(unsigned int agility)
{
	agility_ = agility;
}
void Enemy::setAccelaration(vector3df acc)
{
	accelaration = acc;
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
void Enemy::setRadius(unsigned int rad)
{
	radius_ = rad;
}

vector3df Enemy::getVelocity()
{
	return velocity;
}

vector3df Enemy::getPath()
{
	return destination_;
}
vector3df Enemy::getPosition()
{
	return position;
}
vector3df Enemy::getRotation()
{
	return orientation;
}
unsigned int Enemy::getMaxSpeed()
{
	return maxspeed_;
}
unsigned int Enemy::getAgility()
{
	return agility_;
}
vector3df Enemy::getAccelaration()
{
	return accelaration;
}
unsigned int Enemy::getDamage()
{
	return damage_;
}
unsigned int Enemy::getLoS()
{
	return lineofsightrange_;
}
unsigned int Enemy::getRadius()
{
	return radius_;
}

signed int Enemy::getHealth()
{
	return health_;
}

void Enemy::chase(vector3df target)
{
	//get the positions
	vector3df selfPos = this->getPosition();

	vector3df distancetoTarget = target - selfPos;

	if(distancetoTarget.getLengthSQ() <= 4000)
	{
		//set state to chasing/attacking
		this->velocity = distancetoTarget;
		this->velocity.normalize();
		this->velocity *= 300;
		this->position += this->velocity;
	}
}

Enemy::~Enemy(void)
{
}
