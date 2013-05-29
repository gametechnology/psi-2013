#ifndef Enemy_h
#define Enemy_h

#include <string>
#include <iostream>

#include <Engine/GameObject.h>
#include <Engine/MeshComponent.h>

#include "ArrayList.h"
#include "Player.h"
#include "NetworkInterface.h"


/*
* This class requires a full refactor, there
* is too much functionality and there is no
* documentation.
*/

class Enemy : public GameObject
{
public:
	static int newEnemyId;

	Enemy(irr::scene::ISceneManager*);
	~Enemy();

	enum EnemyType {
		ASTROID = 0,

		DRONE = 1,

		FIGHTER = 2
	};

	virtual void init();
	virtual void onAdd();

	bool isWithinLoS(/*playership class*/);

	std::vector<GameObject*> inRangeList;

	void setMesh(std::string path);
	void setPath(irr::core::vector3df destination);
	void setMaxSpeed(unsigned int maxspeed);
	void setAgility(unsigned int agility);
	void setDamage(unsigned int damage);
	void setLoS(unsigned int los);
	void setHealth(signed int health);
	void setMaxHealth(unsigned int maxhealth);
	void setOriginalRadius(float origradius);
	void setOuterRadius(float outerradius);
	void setOriginalVelocity(irr::core::vector3df origvelocity);
	void setType(EnemyType type);

	//it can only be set as a client, the server makes their own id.
	void setId(int id);
	
	irr::core::vector3df getPath();

	unsigned int getMaxSpeed();
	unsigned int getAgility();
	unsigned int getDamage();
	unsigned int getLoS();

	float getOriginalRadius();
	float getOuterRadius();

	irr::core::vector3df getTarget();
	irr::core::vector3df getOriginalVelocity();
	void chase(irr::core::vector3df target);
	void flee(irr::core::vector3df target);
	void setTarget(irr::core::vector3df target);

	void receiveDamage(int damage);

	void steering(irr::core::vector3df rotational, irr::core::vector3df playerPos);
	void wander();
	int getHealth();
	int getMaxHealth();
	int getId();
	bool isAlive();
	EnemyType getType();

	void updateHealth();
	virtual void update();
	virtual void handleMessage(unsigned int, void* data = 0) { };
protected:
	EnemyType _type;
private:
	irr::scene::ISceneManager* _smgr;
	void applySpeed();

	void pathFinding();
	
	irr::core::vector3df destination_;
	irr::core::vector3df originalvelocity_;
	signed int _health;
	unsigned int _maxHealth;

	float originalradius_;
	float outerradius_;

	unsigned int maxspeed_;
	unsigned int agility_;
	unsigned int damage_;
	unsigned int lineofsightrange_;
	irr::core::vector3df _target;

	int _wanderTime;
	bool _isAlive;

	int _id;

	int healthTimer;
};
#endif
