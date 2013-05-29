#include "Enemy.h"

using namespace irr;
using namespace irr::core;

int Enemy::newEnemyId = 0;

Enemy::Enemy() : GameObject()
{

}

Enemy::Enemy(irr::scene::ISceneManager* smgr) : GameObject()
{
	_smgr = smgr;
}

void Enemy::init()
{
	GameObject::init();

	this->_wanderTime = 0;
	this->healthTimer = 0;
	this->_isAlive = true;
	if(Network::GetInstance()->IsServer())
	{
		this->_id = this->newEnemyId++;
	}
}

int Enemy::getId()
{
	return this->_id;
}

bool Enemy::isAlive()
{
	return this->_isAlive;
}

Enemy::EnemyType Enemy::getType()
{
	return this->_type;
}

void Enemy::setId(int id)
{
	if(!Network::GetInstance()->IsServer())
	{
		this->_id = id;
	}
}

void Enemy::setType(Enemy::EnemyType type)
{
	this->_type = type;
}

void Enemy::pathFinding()
{
	//TODO
}

void Enemy::update()
{
	applySpeed();
	GameObject::update();
}

void Enemy::updateHealth()
{
	if(this->_isAlive)
	{
		this->healthTimer++;
		if(this->healthTimer >= 100)
		{
			{
				receiveDamage(10);
			}
			this->healthTimer=0;
		}
	}
}

bool isWithinLoS(/*playership class*/)
{
	return false;
}

void Enemy::applySpeed()
{
	if (_velocity->getLength() > maxspeed_)
	{
		vector3df cappedvel = _velocity->normalize();
		cappedvel *= (float)maxspeed_;
		_velocity = &cappedvel;
	}
}

void Enemy::steering(vector3df rotational, vector3df playerPos)
{
	matrix4 matX;
	matrix4 matY;
	matrix4 matZ;
	float mData[16];

	mData[0] = 1;
	mData[1] = 0;
	mData[2] = 0;
	mData[3] = 0;

	mData[4] = 0;
	mData[5] = cos(DEGTORAD *  rotational.X);
	mData[6] = -sin(DEGTORAD *  rotational.X);
	mData[7] = 0;

	mData[8] = 0;
	mData[9] = sin(DEGTORAD * rotational.X);
	mData[10] = cos(DEGTORAD * rotational.X);
	mData[11] = 0;

	mData[12] = 0;
	mData[13] = 0;
	mData[14] = 0;
	mData[15] = 1;
	matX.setM(mData);

	mData[0] = cos(DEGTORAD *  rotational.Y);
	mData[1] = 0;
	mData[2] = -sin(DEGTORAD *  rotational.Y);
	mData[3] = 0;

	mData[4] = 0;
	mData[5] = 1;
	mData[6] = 0;
	mData[7] = 0;

	mData[8] = sin(DEGTORAD *  rotational.Y);
	mData[9] = 0;
	mData[10] = cos(DEGTORAD *  rotational.Y);
	mData[11] = 0;

	mData[12] = 0;
	mData[13] = 0;
	mData[14] = 0;
	mData[15] = 1;
	matY.setM(mData);

	mData[0] = cos(DEGTORAD * rotational.Z);
	mData[1] = -sin(DEGTORAD * rotational.Z);
	mData[2] = 0;
	mData[3] = 0;

	mData[4] = sin(DEGTORAD * rotational.Z);
	mData[5] = cos(DEGTORAD * rotational.Z);
	mData[6] = 0;
	mData[7] = 0;

	mData[8] = 0;
	mData[9] = 0;
	mData[10] = 1;
	mData[11] = 0;

	mData[12] = 0;
	mData[13] = 0;
	mData[14] = 0;
	mData[15] = 1;
	matZ.setM(mData);

	matY = matY.operator*(matZ);
	matX = matX.operator*(matY);


	vector3df newvelocity;
	float mData2[4];
	mData2[0] = _velocity->X;
	mData2[1] = _velocity->Y;
	mData2[2] = _velocity->Z;
	mData2[3] = 1;

	matX.multiplyWith1x4Matrix(mData2);

	newvelocity.X = mData2[0];
	newvelocity.Y = mData2[1];
	newvelocity.Z = mData2[2];

	setOriginalVelocity(*_velocity);
	setVelocity(&newvelocity);

	float magnitude = sqrt(pow(_velocity->X,2) + pow(_velocity->Y,2) + pow(_velocity->Z,2));
	vector3df normalizedvelocity = vector3df((_velocity->X/magnitude), (_velocity->Y/magnitude), (_velocity->Z/magnitude));

	vector3df diffPos;
	diffPos.Y = _position->Y - playerPos.Y;
	diffPos.normalize();

	_rotation = &vector3df((RADTODEG * asin(diffPos.Y)), (RADTODEG * acos(diffPos.X)), _rotation->Z);
}

void Enemy::setMesh(std::string path)
{
	component = new MeshComponent(_smgr);
	addComponent(component);
	component->createMeshNode(path);
}
void Enemy::setPath(vector3df destination)
{
	destination_ = destination;
}
void Enemy::setMaxSpeed(unsigned int maxspeed)
{
	maxspeed_ = maxspeed;
}
void Enemy::setAgility(unsigned int agility)
{
	agility_ = agility;
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
	this->_health = health;
}
void Enemy::setMaxHealth(unsigned int maxhealth)
{
	this->_maxHealth = maxhealth;
	setHealth(maxhealth);
}

void Enemy::setOriginalRadius(float origradius)
{
	originalradius_ = origradius;
}
void Enemy::setOuterRadius(float outerradius)
{
	outerradius_ = outerradius;
}

void Enemy::setOriginalVelocity(vector3df origvelocity)
{
	originalvelocity_ = origvelocity;
}

void Enemy::setTarget(vector3df targetPosition)
{
	_target = targetPosition;
}

vector3df Enemy::getTarget()
{
	return _target;
}

vector3df Enemy::getPath()
{
	return destination_;
}

unsigned int Enemy::getMaxSpeed()
{
	return maxspeed_;
}

unsigned int Enemy::getAgility()
{
	return agility_;
}

unsigned int Enemy::getDamage()
{
	return damage_;
}

unsigned int Enemy::getLoS()
{
	return lineofsightrange_;
}

float Enemy::getOriginalRadius()
{
	return originalradius_;
}

float Enemy::getOuterRadius()
{
	return outerradius_;
}

vector3df Enemy::getOriginalVelocity()
{
	return originalvelocity_;
}

int Enemy::getHealth()
{
	return this->_health;
}

int Enemy::getMaxHealth()
{
	return this->_maxHealth;
}

void Enemy::chase(vector3df target)
{
	//get the positions
	vector3df selfPos = *_position;

	vector3df distancetoTarget = target - selfPos;

	//set state to chasing/attacking
	*_velocity = distancetoTarget;
	_velocity->normalize();
	*_velocity *= 0.005f;
	*_position += *_velocity;	
}
void Enemy::flee(vector3df target)
{
	vector3df selfPos = *_position;
	vector3df distancetoTarget = selfPos-target;
	*_velocity = distancetoTarget;
	_velocity->normalize();
	*_velocity *= 0.005f;
	*_position += *_velocity;
}

void Enemy::receiveDamage(int damage)
{
	this->_health -= damage;
	if(this->_health <= 0)
	{
		this->_health = 0;
		this->_isAlive = false;
	}
}

void Enemy::wander()
{
	_wanderTime++;
	int velX = rand()%20-10;
	int velY = rand()%20-10;
	int velZ = rand()%20-10;

	//std::cout << this->_wanderTime << std::endl;
	if(_wanderTime >= 1000)
	{
		_velocity->X +=velX * 0.1f;
		_velocity->Y +=velY * 0.1f;
		_velocity->Z +=velZ * 0.1f;
		_velocity->normalize();
		*_velocity *= 0.01f;
		_wanderTime = 0;
	}
}


Enemy::~Enemy()
{
}
