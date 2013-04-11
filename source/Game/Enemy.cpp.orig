#include "Enemy.h"


Enemy::Enemy(void): Entity(parent)
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
		unsigned int health): Entity(parent)
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
	this->chase(vector3df(3000,30,30));
}

void Enemy::update()
{
	pathFinding();
}

bool isWithinLoS(/*playership class*/)
{
	return false;
}

void Enemy::setState()
{
	//TODO
}
void Enemy::getState()
{
	//TODO
}

void Enemy::applySpeed()
{
	if (accelaration.getLength() > maxaccelaration_)
	{
		vector3df cappedacc = accelaration.normalize();
		cappedacc *= maxaccelaration_;
		accelaration = cappedacc;
	}

	if (velocity.getLength() > maxspeed_)
	{
		vector3df cappedvel = velocity.normalize();
		cappedvel *= maxspeed_;
		velocity = cappedvel;
	}
	velocity += accelaration;
	position += velocity;
}

void Enemy::steeRing()
{

}

void Enemy::contactResolverB()
{
	velocity *= -1;
}

void Enemy::contactResolverA()
{
	//TODO advanced collision resolving
}

void Enemy::contactGenerator()
{

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
