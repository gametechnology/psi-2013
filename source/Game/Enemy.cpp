#include "Enemy.h"
#include <string>
#include <iostream>
#include "Engine/IrrlichtNode.h"
#include "HealthComponent.h"
#include "SectorTemplate.h"

int Enemy::newEnemyId = 0;

Enemy::Enemy(void): Entity()
{
	healthCom_ = new HealthComponent();
}

void Enemy::init()
{
	Entity::init();

	this->_wanderTime = 0;
	this->healthTimer = 0;
	this->_isAlive = true;
	if(Network::GetInstance()->IsServer())
	{
		this->_id = this->newEnemyId++;
	}
}

void Enemy::onAdd()
{
	Entity::onAdd();

	addComponent(healthCom_);
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
	Entity::update();
	if (this->getHealth() <= 0)
	{
		((SectorTemplate*)this->parent)->removeEnemyFromList(this);

		this->destroy();
	}
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
	if (this->transform->velocity.getLength() > maxspeed_)
	{
		vector3df cappedvel = this->transform->velocity.normalize();
		cappedvel *= (float)maxspeed_;
		this->transform->velocity = cappedvel;
	}
}

void Enemy::steering(irr::core::vector3df rotational, irr::core::vector3df playerPos)
{

	irr::core::matrix4 matX;
	irr::core::matrix4 matY;
	irr::core::matrix4 matZ;
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
	mData[9] = sin( DEGTORAD * rotational.X);
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


	irr::core::vector3df newvelocity;
	float mData2[4];
	mData2[0] = this->transform->velocity.X;
	mData2[1] = this->transform->velocity.Y;
	mData2[2] = this->transform->velocity.Z;
	mData2[3] = 1;

	matX.multiplyWith1x4Matrix(mData2);

	newvelocity.X = mData2[0];
	newvelocity.Y = mData2[1];
	newvelocity.Z = mData2[2];

	this->setOriginalVelocity(this->transform->velocity);
	this->transform->velocity = newvelocity;

	float magnitude = sqrt(pow(this->transform->velocity.X,2) + pow(this->transform->velocity.Y,2) + pow(this->transform->velocity.Z,2));
	vector3df normalizedvelocity = vector3df((this->transform->velocity.X/magnitude),(this->transform->velocity.Y/magnitude),(this->transform->velocity.Z/magnitude));

	irr::core::vector3df diffPos;
	diffPos.Y = this->getPosition().Y - playerPos.Y;
	diffPos.normalize();

	this->transform->rotation.X = RADTODEG * asin(diffPos.Y);
	this->transform->rotation.Y = RADTODEG * acos(diffPos.X);
}

void Enemy::contactResolverA(Enemy* _input)
{
	double deltamass = (this->getRadius() / _input->getRadius());
	vector3df deltavelocity = this->getVelocity() - _input->getVelocity();
	vector3df componentThisToBal = Collision::componentOnto(_input->getPosition() - this->transform->position, deltavelocity);
	vector3df componentNormalToBal = deltavelocity - componentThisToBal;
	vector3df thisMassComponent = componentThisToBal * (float)(((deltamass- 1) / (deltamass + 1)));
	vector3df balMassComponent = componentThisToBal * (float)((2 * deltamass / (deltamass + 1)));
	this->transform->velocity = (componentNormalToBal + thisMassComponent + _input->getVelocity());
	_input->setVelocity(balMassComponent + _input->getVelocity());
	this->setRadius(this->getRadius()*2 - this->getPosition().getDistanceFrom(_input->getPosition()));
	_input->setRadius(this->getRadius());
}

void Enemy::setVisualWithPath(const irr::io::path& path)
{
	this->addChild(new IrrlichtNode(path));
}

void Enemy::setVelocity(vector3df velocity)
{
	this->transform->velocity = velocity;
}
void Enemy::setPath(vector3df destination)
{
	destination_ = destination;
}
void Enemy::setPosition(vector3df pos)
{
	this->transform->position = pos;
}
void Enemy::setRotation(vector3df rotategoal)
{
	rotategoal.X = rotategoal.X * this->getAgility();
	rotategoal.Y = rotategoal.Y * this->getAgility();
	rotategoal.Z = rotategoal.Z * this->getAgility();
	this->transform->rotation = rotategoal;
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
	this->transform->acceleration = acc;
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
	healthCom_->setHealth(health);
}
void Enemy::setMaxHealth(unsigned int maxhealth)
{
	healthCom_->setMaxHealth(maxhealth);
}
void Enemy::setRadius(float rad)
{
	radius_ = rad;
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
	return Enemy::_target;
}

vector3df Enemy::getVelocity()
{
	return this->transform->velocity;
}

vector3df Enemy::getPath()
{
	return destination_;
}

vector3df Enemy::getPosition()
{
	return this->transform->position;
}

vector3df Enemy::getRotation()
{
	return this->transform->rotation;
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
	return this->transform->acceleration;
}

unsigned int Enemy::getDamage()
{
	return damage_;
}

unsigned int Enemy::getLoS()
{
	return lineofsightrange_;
}

float Enemy::getRadius()
{
	return radius_;
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
	return healthCom_->getHealth();
}

int Enemy::getMaxHealth()
{
	return healthCom_->getMaxHealth();
}

void Enemy::chase(vector3df target)
{
	//get the positions
	vector3df selfPos = this->getPosition();

	vector3df distancetoTarget = target - selfPos;

	//set state to chasing/attacking
	this->transform->velocity = distancetoTarget;
	this->transform->velocity.normalize();
	this->transform->velocity *= 0.005f;
	this->transform->position += this->transform->velocity;	
}
void Enemy::flee(vector3df target)
{
	vector3df selfPos = this->getPosition();
	vector3df distancetoTarget = selfPos-target;
	this->transform->velocity = distancetoTarget;
	this->transform->velocity.normalize();
	this->transform->velocity *= 0.005f;
	this->transform->position += this->transform->velocity;
}

void Enemy::receiveDamage(int damage)
{
	healthCom_->decreaseHealth(damage);

	if(healthCom_->getHealth() <= 0)
	{
		this->_isAlive = false;
	}
}

void Enemy::wander()
{
	this->_wanderTime++;
	int velX = rand()%20-10;
	int velY = rand()%20-10;
	int velZ = rand()%20-10;

	if(this->_wanderTime >= 1000)
	{
		this->transform->velocity.X +=velX * 0.1f;
		this->transform->velocity.Y +=velY * 0.1f;
		this->transform->velocity.Z +=velZ * 0.1f;
		this->transform->velocity.normalize();
		this->transform->velocity *= 0.01f;
		this->_wanderTime = 0;
	}
}


Enemy::~Enemy(void)
{
	Entity::~Entity();
}
