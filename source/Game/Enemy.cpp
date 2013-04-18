#include "Enemy.h"
#include <string>
#include <iostream>

Enemy::Enemy(void): Entity(parent)
{
	this->_wanderTime = 0;
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
	setMaxHealth(health);
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

void Enemy::steering()
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
		mData[5] = cos(DEGTORAD *  this->getRotation().X);
		mData[6] = -sin(DEGTORAD *  this->getRotation().X);
		mData[7] = 0;

		mData[8] = 0;
		mData[9] = sin( DEGTORAD * this->getRotation().X);
		mData[10] = cos(DEGTORAD * this->getRotation().X);
		mData[11] = 0;

		mData[12] = 0;
		mData[13] = 0;
		mData[14] = 0;
		mData[15] = 1;
		matX.setM(mData);
		
		mData[0] = cos(DEGTORAD *  this->getRotation().Y);
		mData[1] = 0;
		mData[2] = -sin(DEGTORAD *  this->getRotation().Y);
		mData[3] = 0;

		mData[4] = 0;
		mData[5] = 1;
		mData[6] = 0;
		mData[7] = 0;
	
		mData[8] = sin(DEGTORAD *  this->getRotation().Y);
		mData[9] = 0;
		mData[10] = cos(DEGTORAD *  this->getRotation().Y);
		mData[11] = 0;

		mData[12] = 0;
		mData[13] = 0;
		mData[14] = 0;
		mData[15] = 1;
		matY.setM(mData);

		mData[0] = cos(DEGTORAD * this->getRotation().Z);
		mData[1] = -sin(DEGTORAD * this->getRotation().Z);
		mData[2] = 0;
		mData[3] = 0;

		mData[4] = sin(DEGTORAD * this->getRotation().Z);
		mData[5] = cos(DEGTORAD * this->getRotation().Z);
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
		mData2[0] = velocity.X;
		mData2[1] = velocity.Y;
		mData2[2] = velocity.Z;
		mData2[3] = 1;
	
		matX.multiplyWith1x4Matrix(mData2);

		newvelocity.X = mData2[0];
		newvelocity.Y = mData2[1];
		newvelocity.Z = mData2[2];

		this->velocity = newvelocity;
}

void Enemy::contactResolverA(Enemy* _input)
{
    double deltamass = (this->getRadius() / _input->getRadius());
	vector3df deltavelocity = this->getVelocity() - _input->getVelocity();
	vector3df componentThisToBal = componentOnto(_input->getPosition() - this->position, deltavelocity);
    vector3df componentNormalToBal = deltavelocity - componentThisToBal;
    vector3df thisMassComponent = componentThisToBal * ((deltamass- 1) / (deltamass + 1));
	vector3df balMassComponent = componentThisToBal * (2 * deltamass / (deltamass + 1));
    velocity = componentNormalToBal + thisMassComponent + _input->getVelocity();
    _input->setVelocity(balMassComponent + _input->getVelocity());
	this->setRadius(this->getRadius()*2 - this->getPosition().getDistanceFrom(_input->getPosition()));
	_input->setRadius(this->getRadius());
}

vector3df Enemy::componentOnto(vector3df input, vector3df deltavelocity)
{
	return input * (deltavelocity.dotProduct(input) / input.getLengthSQ());
}

void Enemy::contactResolverB()
{
	velocity *= -1;
}

/*void Enemy::contactGenerator(Player* input)
{
	float distance = position.getDistanceFrom(input->position);
	float radii = input->radius_ + radius_;
	if (distance < radii)
	{
		contactResolverB();
	}
}*/

void Enemy::contactGenerator(Enemy* input)
{
	float distance = position.getDistanceFrom(input->getPosition());
	int radii = input->getRadius() + radius_;
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
	rotategoal.X = rotategoal.X * this->getAgility();
	rotategoal.Y = rotategoal.Y * this->getAgility();
	rotategoal.Z = rotategoal.Z * this->getAgility();
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
void Enemy::setMaxHealth(unsigned int maxhealth)
{
	maxhealth_ = maxhealth;
	setHealth(maxhealth);
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

void Enemy::setTarget(vector3df targetPosition)
{
	Enemy::_target = targetPosition;
}

vector3df Enemy::getTarget()
{
	return Enemy::_target;
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

signed int Enemy::getHealth()
{
	return health_;
}

unsigned int Enemy::getMaxHealth()
{
	return maxhealth_;
}

void Enemy::chase(vector3df target)
{
	//get the positions
	vector3df selfPos = this->getPosition();

	vector3df distancetoTarget = target - selfPos;
	
		//set state to chasing/attacking
		this->velocity = distancetoTarget;
		this->velocity.normalize();
		this->velocity *= 0.005f;
		this->position += this->velocity;	
}
void Enemy::flee(vector3df target)
{
	vector3df selfPos = this->getPosition();
	vector3df distancetoTarget = selfPos-target;
	this->velocity = distancetoTarget;
	this->velocity.normalize();
	this->velocity *= 0.005f;
	this->position += this->velocity;
}

void Enemy::wander()
{
	this->_wanderTime++;
	int velX = rand()%20-10;
	int velY = rand()%20-10;
	int velZ = rand()%20-10;

	if(this->_wanderTime >= 10000)
	{
		this->velocity.X +=velX * 0.1f;
		this->velocity.Y +=velY * 0.1f;
		this->velocity.Z +=velZ * 0.1f;
		this->velocity.normalize();
		this->velocity *= 0.01f;
		//std::cout <<  "----- X: " << this->velocity.X << ", Y: "<< this->velocity.Y << ", Z: "<< this->velocity.Z;
		this->_wanderTime = 0;
	}
}
Enemy::~Enemy(void)
{
	Entity::~Entity();
}
